#pragma once

#include "device.hpp"
#include "renderer/pipeline.hpp"
#include "webgpu/webgpu_cpp.h"
#include <utility>
#include <vector>

namespace bingusengine {
namespace renderer {

class Pipeline;

class Swapchain {
  public:
	Swapchain(Device &device, Window &window, wgpu::Surface &surface);
	~Swapchain();

	void configureSurface();

	std::vector<std::reference_wrapper<Pipeline>> pipelines;

	wgpu::SurfaceCapabilities getSurfaceCapabilities();

	std::pair<wgpu::SurfaceTexture, wgpu::TextureView> getNextSurfaceViewData();

  private:
	Device &device;
	Window &window;

	wgpu::Surface &surface;

	wgpu::Extent2D windowSize;
};


} // namespace renderer
} // namespace bingusengine
