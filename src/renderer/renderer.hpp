#pragma once

#include "buffer.hpp"
#include "device.hpp"
#include "pipeline.hpp"
#include "swapchain.hpp"
#include "window.hpp"

namespace bingusengine {

class Renderer {
  public:
	Renderer();
	~Renderer();

	void renderFrame();
	
	Buffer<float> &getVertexBuffer() { return vertexBuffer; }

  private:
	Window window;
	Device device;

	WGPUSurface surface;
	Swapchain swapchain;
	Pipeline mainPipeline;

	Buffer<float> vertexBuffer =
		Buffer<float>(device, WGPUBufferUsage_CopyDst | WGPUBufferUsage_Vertex,
					  15 * sizeof(float));
	
	WGPUCommandEncoder createCommandEncoder();
};

} // namespace bingusengine
