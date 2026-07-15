#pragma once

#include "device.hpp"
#include "swapchain.hpp"
#include "webgpu/webgpu_cpp.h"
#include <cstddef>
#include <string>
#include <vector>

namespace bingusengine {

class Pipeline {
	struct VertexBufferLayoutInfo {
		wgpu::VertexBufferLayout layouts;
		size_t count;
	};

  public:
	Pipeline(Device &device, Swapchain &swapchain);
	~Pipeline();

	wgpu::RenderPipeline getPipeline() { return pipeline; };

  private:
	Device &device;
	Swapchain &swapchain;

	wgpu::RenderPipeline pipeline;

	std::vector<wgpu::VertexAttribute> vertexAttributes;
	VertexBufferLayoutInfo getVertexBufferLayouts();
	void filloutPipelineLayoutDesc();

	void initializePipeline();

	void initVertexStage(wgpu::RenderPipelineDescriptor &pipelineDesc,
						 wgpu::ShaderModule &shaderModule);
	void initPrimitiveStage(wgpu::RenderPipelineDescriptor &pipelineDesc);
	void initFragmentStage(wgpu::RenderPipelineDescriptor &pipelineDesc,
						   wgpu::ShaderModule &shaderModule);
	void initDepthStencilStage(wgpu::RenderPipelineDescriptor &pipelineDesc);
	void initMultisampling(wgpu::RenderPipelineDescriptor &pipelineDesc);

	wgpu::ColorTargetState configureColorTarget();

	wgpu::ShaderModule createShaderModule(std::string path);

	std::string readFile(const char *path);

	wgpu::PipelineLayoutDescriptor pipelineLayoutDesc{};

	Pipeline::VertexBufferLayoutInfo vertexBufferLayout;
	wgpu::FragmentState fragmenetState{};

	wgpu::BlendState blendState{};
	wgpu::ColorTargetState colorTarget;
};

} // namespace bingusengine
