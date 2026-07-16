#include "device.hpp"
#include "sdl3webgpu.hpp"
#include "webgpu/webgpu_cpp.h"
#include "window.hpp"
#include <iostream>
#include <stdexcept>
#include <string_view>

namespace bingusengine {
namespace renderer {

Device::Device(Window &window) : window(window) {

	createInstance();
	std::cout << "created webgpu instance!" << std::endl;

	setupAdapter();
	std::cout << "got webgpu adapter!" << std::endl;

	setupDevice();
	std::cout << "got upgrade my code into usingwebgpu device!" << std::endl;

	queue = device.GetQueue();
	std::cout << "got webgpu queue!" << std::endl;
}

Device::~Device() {}

void Device::submitCommandBuffer(wgpu::CommandBuffer cmdBuffer) {
	queue.Submit(1, &cmdBuffer);
}

void Device::createInstance() {
	wgpu::InstanceFeatureName timedWaitAny =
		wgpu::InstanceFeatureName::TimedWaitAny;

	wgpu::InstanceDescriptor desc{};
	desc.requiredFeatureCount = 1;
	desc.requiredFeatures = &timedWaitAny;

	instance = wgpu::CreateInstance(&desc);
	if (!instance) {
		throw std::runtime_error("unable to create a webgpu instance!");
	}
}

void Device::setupAdapter() {
	wgpu::RequestAdapterOptions options{};
	options.compatibleSurface =
		SDL_GetWGPUSurface(instance, window.getWindow());

	options.nextInChain = nullptr;

	struct UserData {
		wgpu::Adapter adapter = nullptr;
		bool requestEnded = false;
	};
	UserData userData;

	auto onAdapterRequestEnded = [](wgpu::RequestAdapterStatus status,
									wgpu::Adapter adapter,
									wgpu::StringView message, void *userdata) {
		UserData &userData = *reinterpret_cast<UserData *>(userdata);

		if (status == wgpu::RequestAdapterStatus::Success) {
			userData.adapter = adapter;
		} else {
			throw std::runtime_error("unable to get a webgpu adapter!");
		}
		userData.requestEnded = true;
	};

	wgpu::Future future =
		instance.RequestAdapter(&options, wgpu::CallbackMode::WaitAnyOnly,
								onAdapterRequestEnded, &userData);

	instance.WaitAny(future, /*timeoutNS=*/10'000'000'000ULL);

	adapter = userData.adapter;

	// inspection
	wgpu::AdapterInfo adapterInfo{};
	adapter.GetInfo(&adapterInfo);
	std::cout << "GPU Selected: "
			  << static_cast<std::string_view>(adapterInfo.device) << std::endl;
}

void Device::setupDevice() {
#ifdef NDEBUG
	const char *disableToggles[] = {"skip_validation",
									"enable_backend_validation"};
	uint32_t disableCount = 2;
#else
	const char **disableToggles = nullptr;
	uint32_t disableCount = 0;
#endif
	wgpu::DawnTogglesDescriptor toggleDesc{};
	toggleDesc.sType = wgpu::SType::DawnTogglesDescriptor;
	toggleDesc.nextInChain = nullptr;
	toggleDesc.disabledToggles = disableToggles;
	toggleDesc.disabledToggleCount = disableCount;

	wgpu::DeviceDescriptor desc{};
	desc.label = "wgpu device lol";

	desc.requiredFeatureCount = 0;
	desc.requiredFeatures = nullptr;

	desc.requiredLimits = nullptr;

	desc.defaultQueue.label = "the default queue lol";

	desc.nextInChain = &toggleDesc;

	desc.SetUncapturedErrorCallback([](const wgpu::Device &,
									   wgpu::ErrorType type,
									   wgpu::StringView message) {
		std::cout << "DAWN Error: type " << static_cast<uint32_t>(type);
		if (message.length != wgpu::kStrlen) {
			std::cout << " (" << static_cast<std::string_view>(message) << ")";
		}
		std::cout << std::endl;
	});

	device = requestDeviceSync(&desc);
}

wgpu::Device
Device::requestDeviceSync(const wgpu::DeviceDescriptor *descriptor) {
	struct UserData {
		wgpu::Device device = nullptr;
		bool requestEnded = false;
	};
	UserData userData;

	auto onDeviceRequestEnded = [](wgpu::RequestDeviceStatus status,
								   wgpu::Device device,
								   wgpu::StringView message, void *userdata) {
		UserData &userData = *reinterpret_cast<UserData *>(userdata);

		if (status == wgpu::RequestDeviceStatus::Success) {
			userData.device = device;
		} else {
			throw std::runtime_error("unable to get a webgpu device!");
		}
		userData.requestEnded = true;
	};

	wgpu::Future future =
		adapter.RequestDevice(descriptor, wgpu::CallbackMode::WaitAnyOnly,
							  onDeviceRequestEnded, &userData);

	adapter.GetInstance().WaitAny(future, /*timeoutNS=*/10'000'000'000ULL);

	return userData.device;
}

} // namespace renderer
} // namespace bingusengine
