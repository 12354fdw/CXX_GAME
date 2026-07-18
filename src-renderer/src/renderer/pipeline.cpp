#include "pipeline.hpp"
#include "device.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/vector_float3.hpp"
#include "renderer/mesh.hpp"
#include "renderer/texture.hpp"
#include "renderer/window.hpp"
#include "swapchain.hpp"
#include "utils.hpp"
#include "webgpu/webgpu_cpp.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace bingusengine {
namespace renderer {
Pipeline::Pipeline(Device &device, Window &window, Swapchain &swapchain)
	: device(device), window(window), swapchain(swapchain) {
	initializePipeline();
}

Pipeline::~Pipeline() {}
void Pipeline::initializePipeline() {
	wgpu::ShaderModule shaderModule = createShaderModule("shader/main.wgsl");

	wgpu::RenderPipelineDescriptor pipelineDesc{};

	initVertexStage(pipelineDesc, shaderModule);
	initPrimitiveStage(pipelineDesc);
	initFragmentStage(pipelineDesc, shaderModule);
	initDepthStencilStage(pipelineDesc);
	initMultisampling(pipelineDesc);

	filloutPipelineLayoutDesc();
	pipelineDesc.layout =
		device.getDevice().CreatePipelineLayout(&pipelineLayoutDesc);

	pipeline = device.getDevice().CreateRenderPipeline(&pipelineDesc);
}

void Pipeline::filloutPipelineLayoutDesc() {
	pipelineLayoutDesc.bindGroupLayoutCount = 0;
	pipelineLayoutDesc.bindGroupLayouts = nullptr;

	pipelineLayoutDesc.immediateSize = sizeof(glm::mat4);
}

Pipeline::VertexBufferLayoutInfo Pipeline::getVertexBufferLayouts() {
	Pipeline::VertexBufferLayoutInfo info{};

	wgpu::VertexBufferLayout vertexBufferLayout{};

	vertexAttributes.push_back(
		(wgpu::VertexAttribute){.format = wgpu::VertexFormat::Float32x3,
								.offset = 0,
								.shaderLocation = 0}); // position

	vertexAttributes.push_back(
		(wgpu::VertexAttribute){.format = wgpu::VertexFormat::Float32x3,
								.offset = sizeof(glm::vec3),
								.shaderLocation = 1}); // color

	vertexBufferLayout.attributes = vertexAttributes.data();
	vertexBufferLayout.attributeCount = vertexAttributes.size();

	vertexBufferLayout.arrayStride = sizeof(Vertex);
	vertexBufferLayout.stepMode = wgpu::VertexStepMode::Vertex;

	info.layouts = vertexBufferLayout;
	info.count = 1;

	return info;
}

void Pipeline::initVertexStage(wgpu::RenderPipelineDescriptor &pipelineDesc,
							   wgpu::ShaderModule &shaderModule) {

	vertexBufferLayout = getVertexBufferLayouts();

	pipelineDesc.vertex.bufferCount = vertexBufferLayout.count;
	pipelineDesc.vertex.buffers = &vertexBufferLayout.layouts;

	pipelineDesc.vertex.module = shaderModule;
	pipelineDesc.vertex.entryPoint = "vs_main";
	pipelineDesc.vertex.constantCount = 0;
	pipelineDesc.vertex.constants = nullptr;
}

void Pipeline::initPrimitiveStage(
	wgpu::RenderPipelineDescriptor &pipelineDesc) {
	pipelineDesc.primitive.topology = wgpu::PrimitiveTopology::TriangleList;

	pipelineDesc.primitive.stripIndexFormat = wgpu::IndexFormat::Undefined;

	pipelineDesc.primitive.frontFace = wgpu::FrontFace::CCW;
	pipelineDesc.primitive.cullMode = wgpu::CullMode::Back;
}

void Pipeline::initFragmentStage(wgpu::RenderPipelineDescriptor &pipelineDesc,
								 wgpu::ShaderModule &shaderModule) {
	fragmentState.module = shaderModule;
	fragmentState.entryPoint = "fs_main";
	fragmentState.constantCount = 0;
	fragmentState.constants = nullptr;

	colorTarget = configureColorTarget();
	fragmentState.targetCount = 1;
	fragmentState.targets = &colorTarget;

	pipelineDesc.fragment = &fragmentState;
}

void Pipeline::initDepthStencilStage(
	wgpu::RenderPipelineDescriptor &pipelineDesc) {
	depthStencilState.depthCompare = wgpu::CompareFunction::Less;
	depthStencilState.depthWriteEnabled = true;

	wgpu::TextureFormat depthTextureFormat = wgpu::TextureFormat::Depth24Plus;
	depthStencilState.format = depthTextureFormat;

	depthStencilState.stencilReadMask = 0;
	depthStencilState.stencilWriteMask = 0;

	wgpu::Extent2D windowSize = window.getWindowSize();

	depthTexture.emplace(Texture(device, depthTextureFormat,
								 wgpu::TextureAspect::DepthOnly,
								 wgpu::TextureUsage::RenderAttachment,
								 {windowSize.width, windowSize.height, 1}));

	pipelineDesc.depthStencil = &depthStencilState;
}

void Pipeline::initMultisampling(wgpu::RenderPipelineDescriptor &pipelineDesc) {
	pipelineDesc.multisample.count = 1;
	pipelineDesc.multisample.mask = ~0u;
	pipelineDesc.multisample.alphaToCoverageEnabled = false;
}

wgpu::ColorTargetState Pipeline::configureColorTarget() {

	// color
	blendState.color.srcFactor = wgpu::BlendFactor::SrcAlpha;
	blendState.color.dstFactor = wgpu::BlendFactor::OneMinusSrcAlpha;
	blendState.color.operation = wgpu::BlendOperation::Add;

	// alpha
	blendState.alpha.srcFactor = wgpu::BlendFactor::Zero;
	blendState.alpha.dstFactor = wgpu::BlendFactor::One;
	blendState.alpha.operation = wgpu::BlendOperation::Add;

	wgpu::ColorTargetState colorTarget{};

	wgpu::SurfaceCapabilities capabilities = swapchain.getSurfaceCapabilities();

	colorTarget.format = capabilities.formats[0];
	colorTarget.blend = &blendState;
	colorTarget.writeMask = wgpu::ColorWriteMask::All;

	return colorTarget;
}

wgpu::ShaderModule Pipeline::createShaderModule(std::string path) {
	wgpu::ShaderModuleDescriptor shaderDesc;

	wgpu::ShaderSourceWGSL shaderCodeDesc{};
	std::string shaderSource = readFile(path.c_str());
	shaderCodeDesc.code = WSTR(shaderSource);

	shaderDesc.nextInChain = &shaderCodeDesc;

	return device.getDevice().CreateShaderModule(&shaderDesc);
}

std::string Pipeline::readFile(const char *path) {
	std::ifstream file(path);
	if (!file.is_open()) {
		throw std::runtime_error("unable to open shader file!");
	}

	std::stringstream buffer;
	buffer << file.rdbuf();

	std::string content = buffer.str();

	return content;
}

} // namespace renderer
} // namespace bingusengine
