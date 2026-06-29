#pragma once

#include "device.hpp"
#include "webgpu/webgpu.h"
#include <utility>

namespace bingusengine {

class Swapchain {
  public:
	Swapchain(Device &device, WGPUSurface &surface);

	void configureSurface();

	std::pair<WGPUSurfaceTexture, WGPUTextureView> getNextSurfaceViewData();

  private:
	Device device;

	WGPUSurface surface;
};

} // namespace bingusengine


