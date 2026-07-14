#pragma once

#include "webgpu/webgpu.h"
#include "window.hpp"
#define WEBGPU_CPP_IMPLEMENTATION
#include <webgpu/webgpu_cpp.h>

namespace bingusengine {
class Device {
  public:
	Device(Window &window);
	~Device();

	// getters
	const WGPUInstance &getInstance() { return instance; }
	const WGPUAdapter &getAdapter() { return adapter; }
	const WGPUDevice &getDevice() { return device; }
	const WGPUQueue &getQueue() { return queue; }

	const WGPUInstance &getInstance() const { return instance; }
	const WGPUAdapter &getAdapter() const { return adapter; }
	const WGPUDevice &getDevice() const { return device; }
	const WGPUQueue &getQueue() const { return queue; }

	void submitCommandBuffer(WGPUCommandBuffer cmdBuffer);

  private:
	Window &window;

	WGPUInstance instance;
	WGPUAdapter adapter;
	WGPUDevice device;
	WGPUQueue queue;

	void createInstance();
	void setupAdapter();
	void setupDevice();
	void setupErrorCallback();

	WGPUDevice requestDeviceSync(WGPUDeviceDescriptor const *descriptor);
};

} // namespace bingusengine
