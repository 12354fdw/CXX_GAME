#pragma once

#include "device.hpp"
#include "pipeline.hpp"
#include "swapchain.hpp"
#include "webgpu/webgpu.h"
#include "window.hpp"

namespace bingusengine {

class Renderer {
  public:
	Renderer();
	~Renderer();

	void renderFrame();

  private:
	Window window;
	Device device;

	WGPUSurface surface;
	Swapchain swapchain;
	Pipeline mainPipeline;

	WGPUCommandEncoder createCommandEncoder();
};

} // namespace bingusengine
