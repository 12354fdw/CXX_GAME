#pragma once

#include "device.hpp"
#include "webgpu/webgpu.h"
#include "window.hpp"
#include <utility>

namespace bingusengine {

class Swapchain {
  public:
	Swapchain(Window &window, Device &device);

	void configureSurface();
	void present();

  private:
	Window window;
	Device device;

	WGPUSurface surface;

	std::pair<WGPUSurfaceTexture, WGPUTextureView> getNextSurfaceViewData();
};

} // namespace bingusengine


