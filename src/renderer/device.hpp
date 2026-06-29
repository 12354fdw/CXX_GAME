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
	WGPUInstance getInstance() { return instance; }
	WGPUAdapter getAdapter() { return adapter; }
	WGPUDevice getDevice() { return device; }

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
