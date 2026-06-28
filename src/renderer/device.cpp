#include "device.hpp"
#include "webgpu/webgpu.h"
#include <stdexcept>
#include <thread>
#include <chrono>

namespace renderer {
Device::Device() {
	createInstance();
	getAdapter();
}
Device::~Device() {}

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
				throw std::runtime_error("unable to get an adapter!");
			}
			userData.requestEnded = true;
		};

	wgpuInstanceRequestAdapter(
		instance, &options, onAdaptorRequestEndedCallback, (void *)&userData);

	while (!userData.requestEnded) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	adapter = userData.adapter;
}

}