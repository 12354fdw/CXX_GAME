#pragma once

#include "device.hpp"
#include "webgpu/webgpu_cpp.h"
#include <utility>

namespace bingusengine {

class Swapchain {
  public:
	Swapchain(Device &device, Window &window, wgpu::Surface &surface);
	~Swapchain();

	void configureSurface();

	wgpu::SurfaceCapabilities getSurfaceCapabilities();

	std::pair<wgpu::SurfaceTexture, wgpu::TextureView> getNextSurfaceViewData();

  private:
	Device &device;
	Window &window;

	wgpu::Surface &surface;
};

} // namespace bingusengine
