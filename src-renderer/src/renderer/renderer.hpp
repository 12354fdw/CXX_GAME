#pragma once

#include "device.hpp"
#include "instance.hpp"
#include "pipeline.hpp"
#include "renderer/camera.hpp"
#include "swapchain.hpp"
#include "window.hpp"
#include <vector>

namespace bingusengine {

class Renderer {
  public:
	Renderer();
	~Renderer();

	Camera camera = Camera();

	void renderFrame();

	std::vector<Instance> instances;

	const Device &getDevice() { return device; };

  private:
	Window window;
	Device device;

	wgpu::Surface surface;
	Swapchain swapchain;
	Pipeline mainPipeline;

	wgpu::CommandEncoder createCommandEncoder();
};

} // namespace bingusengine
