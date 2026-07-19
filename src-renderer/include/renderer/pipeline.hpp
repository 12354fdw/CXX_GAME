#pragma once

#include "device.hpp"
#include "renderer/texture.hpp"
#include "renderer/window.hpp"
#include "swapchain.hpp"
#include "webgpu/webgpu_cpp.h"
#include <optional>
#include <string>
#include <vector>

namespace bingusengine {
namespace renderer {

class Swapchain;

class Pipeline {

  public:
	Pipeline(Device &device, Window &window, Swapchain &swapchain);
	~Pipeline();

	void reconfigureDepthTexture();

	wgpu::RenderPipeline getPipeline() { return pipeline; };

	const Texture &getDepthTexture() const { return depthTexture.value(); };

  private:
	Device &device;
	Window &window;
	Swapchain &swapchain;

	wgpu::RenderPipeline pipeline;
	std::optional<Texture> depthTexture;

	std::vector<wgpu::VertexAttribute> meshAttributes;
	std::vector<wgpu::VertexAttribute> instanceAttributes;

	std::vector<wgpu::VertexBufferLayout> getVertexBufferLayouts();
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

	std::vector<wgpu::VertexBufferLayout> vertexBufferLayout;
	wgpu::FragmentState fragmentState{};
	wgpu::DepthStencilState depthStencilState{};

	wgpu::BlendState blendState{};
	wgpu::ColorTargetState colorTarget;
};

} // namespace renderer
} // namespace bingusengine
