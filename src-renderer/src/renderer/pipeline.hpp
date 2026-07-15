#pragma once

#include "device.hpp"
#include "renderer/texture.hpp"
#include "renderer/window.hpp"
#include "swapchain.hpp"
#include "webgpu/webgpu_cpp.h"
#include <cstddef>
#include <optional>
#include <string>
#include <vector>

namespace bingusengine {

class Pipeline {
	struct VertexBufferLayoutInfo {
		wgpu::VertexBufferLayout layouts;
		size_t count;
	};

  public:
	Pipeline(Device &device, Window &window, Swapchain &swapchain);
	~Pipeline();

	wgpu::RenderPipeline getPipeline() { return pipeline; };

	const Texture &getDepthTexture() const { return depthTexture.value(); };

  private:
	Device &device;
	Window &window;
	Swapchain &swapchain;

	wgpu::RenderPipeline pipeline;
	std::optional<Texture> depthTexture;

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
	wgpu::FragmentState fragmentState{};
	wgpu::DepthStencilState depthStencilState{};

	wgpu::BlendState blendState{};
	wgpu::ColorTargetState colorTarget;
};

} // namespace bingusengine
