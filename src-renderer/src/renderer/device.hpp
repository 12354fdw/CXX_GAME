#pragma once

#include "webgpu/webgpu_cpp.h"
#include "window.hpp"

namespace bingusengine {
class Device {
  public:
	Device(Window &window);
	~Device();

	// getters
	const wgpu::Instance &getInstance() { return instance; }
	const wgpu::Adapter &getAdapter() { return adapter; }
	const wgpu::Device &getDevice() { return device; }
	const wgpu::Queue &getQueue() { return queue; }

	const wgpu::Instance &getInstance() const { return instance; }
	const wgpu::Adapter &getAdapter() const { return adapter; }
	const wgpu::Device &getDevice() const { return device; }
	const wgpu::Queue &getQueue() const { return queue; }

	void submitCommandBuffer(wgpu::CommandBuffer cmdBuffer);

  private:
	Window &window;

	wgpu::Instance instance;
	wgpu::Adapter adapter;
	wgpu::Device device;
	wgpu::Queue queue;

	void createInstance();
	void setupAdapter();
	void setupDevice();

	wgpu::Device requestDeviceSync(const wgpu::DeviceDescriptor *descriptor);
};

} // namespace bingusengine
