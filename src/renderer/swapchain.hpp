#pragma once

#include "device.hpp"
#include "webgpu/webgpu.h"
#include <utility>

namespace bingusengine {

class Swapchain {
  public:
	Swapchain(Device &device, Window &window, WGPUSurface &surface);
	~Swapchain();

	void configureSurface();

	WGPUSurfaceCapabilities getSurfaceCapabilities();

	std::pair<WGPUSurfaceTexture, WGPUTextureView> getNextSurfaceViewData();

  private:
	Device &device;
	Window &window;

	WGPUSurface &surface;
};

} // namespace bingusengine
