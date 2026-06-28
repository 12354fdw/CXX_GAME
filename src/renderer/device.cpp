#include "device.hpp"
#include "webgpu/webgpu.h"
#include <iostream>
#include <stdexcept>
#include <thread>
#include <chrono>

namespace renderer {
Device::Device() {
	createInstance();
	std::cout << "created webgpu instance!" << std::endl;

	getAdapter();
	std::cout << "got webgpu adapter!" << std::endl;

	getDevice();
	std::cout << "got webgpu device!" << std::endl;
}
Device::~Device() {
	wgpuAdapterRelease(adapter);
	wgpuInstanceRelease(instance);
	wgpuDeviceRelease(device);
}

void Device::createInstance() {
	WGPUInstanceDescriptor desc{};
	desc.nextInChain = nullptr;

	instance = wgpuCreateInstance(&desc);
	if (!instance) {
		throw std::runtime_error("unable to create a webgpu instance!");
	}
}

void Device::getAdapter() {
	WGPURequestAdapterOptions options{};
	options.nextInChain = nullptr;

	struct UserData {
		WGPUAdapter adapter = nullptr;
		bool requestEnded = false;
	};
	UserData userData;

	auto onAdaptorRequestEndedCallback =
		[](WGPURequestAdapterStatus status, WGPUAdapter adapter,
		   char const *message, void *pUserData) {
			UserData &userData = *reinterpret_cast<UserData *>(pUserData);

			if (status == WGPURequestAdapterStatus_Success) {
				userData.adapter = adapter;
			} else {
				throw std::runtime_error("unable to get a webgpu adapter!");
			}
			userData.requestEnded = true;
		};

	wgpuInstanceRequestAdapter(
		instance, &options, onAdaptorRequestEndedCallback, (void *)&userData);

	while (!userData.requestEnded) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	adapter = userData.adapter;

	// inspection
	WGPUAdapterProperties properties{};
	wgpuAdapterGetProperties(adapter, &properties);
	std::cout << "GPU Selected: " << properties.name << std::endl;
}

void Device::getDevice() {
#if DISABLE_VALIDATION_LAYERS
	const char *disableToggles[] = {"skip_validation",
									"enable_backend_validation"};
	uint32_t disableCount = 2;
#else
	const char **disableToggles = nullptr;
	uint32_t disableCount = 0;
#endif
	WGPUDawnTogglesDescriptor toggleDesc{};
	toggleDesc.chain.sType = WGPUSType_DawnTogglesDescriptor;
	toggleDesc.chain.next = nullptr;
	toggleDesc.disabledToggles = disableToggles;
	toggleDesc.disabledToggleCount = disableCount;

	WGPUDeviceDescriptor desc{};
	desc.label = "wgpu device lol";
	desc.requiredFeatureCount = 0;
	desc.requiredLimits = nullptr;

	desc.defaultQueue.nextInChain = nullptr;
	desc.defaultQueue.label = "the default queue lol";

	desc.nextInChain = reinterpret_cast<const WGPUChainedStruct *>(&toggleDesc);

	device = requestDeviceSync(&desc);
}

WGPUDevice Device::requestDeviceSync(WGPUDeviceDescriptor const *descriptor) {
	struct UserData {
		WGPUDevice device = nullptr;
		bool requestEnded = false;
	};
	UserData userData;

	auto onDeviceRequestEndedCallback =
		[](WGPURequestDeviceStatus status, WGPUDevice device,
		   char const *message, void *pUserData) {
			UserData &userData = *reinterpret_cast<UserData *>(pUserData);

			if (status == WGPURequestDeviceStatus_Success) {
				userData.device = device;
			} else {
				throw std::runtime_error("unable to get a webgpu device!");
			}
			userData.requestEnded = true;
		};

	wgpuAdapterRequestDevice(adapter, descriptor, onDeviceRequestEndedCallback,
							 (void *)&userData);

	while (!userData.requestEnded) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	return userData.device;
}
		
}