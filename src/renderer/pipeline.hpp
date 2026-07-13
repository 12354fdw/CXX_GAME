#pragma once

#include "device.hpp"
#include "swapchain.hpp"
#include "webgpu/webgpu.h"
#include <cstddef>
#include <string>

namespace bingusengine {

class Pipeline {
	struct VertexBufferLayoutInfo {
		WGPUVertexBufferLayout layouts;
		size_t count;
	};

  public:
	Pipeline(Device &device, Swapchain &swapchain);
	~Pipeline();

	WGPURenderPipeline getPipeline() { return pipeline; };

  private:
	Device &device;
	Swapchain &swapchain;

	WGPURenderPipeline pipeline;

	std::vector<WGPUVertexAttribute> vertexAttributes;
	VertexBufferLayoutInfo getVertexBufferLayouts();

	void initializePipeline();

	void initVertexStage(WGPURenderPipelineDescriptor &pipelineDesc,
						 WGPUShaderModule &shaderModule);
	void initPrimitiveStage(WGPURenderPipelineDescriptor &pipelineDesc);
	void initFragmentStage(WGPURenderPipelineDescriptor &pipelineDesc,
						   WGPUShaderModule &shaderModule);
	void initDepthStencilStage(WGPURenderPipelineDescriptor &pipelineDesc);
	void initMultisampling(WGPURenderPipelineDescriptor &pipelineDesc);

	WGPUColorTargetState configureColorTarget();

	WGPUShaderModule createShaderModule(std::string path);

	std::string readFile(const char *path);
};

} // namespace bingusengine
