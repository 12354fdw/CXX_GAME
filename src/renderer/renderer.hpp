#pragma once

#include "device.hpp"
#include "swapchain.hpp"
#include "webgpu/webgpu.h"
#include "window.hpp"

namespace bingusengine {

class Renderer {
  public:
	Renderer(Window *window);
	~Renderer();

	void renderFrame();

  private:
	Window *window;
	Device device;

	WGPUSurface surface;
	Swapchain swapchain;

	WGPUCommandEncoder createCommandEncoder();
};

} // namespace bingusengine
