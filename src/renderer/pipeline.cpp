#include "pipeline.hpp"
#include "device.hpp"
#include "swapchain.hpp"
#include "webgpu/webgpu.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace bingusengine {
Pipeline::Pipeline(Device &device, Swapchain &swapchain)
	: device(device), swapchain(swapchain) {
	initializePipeline();
}

Pipeline::~Pipeline() {}
void Pipeline::initializePipeline() {
	WGPUShaderModule shaderModule = createShaderModule("shader/main.wgsl");

	WGPURenderPipelineDescriptor pipelineDesc{};

	initVertexStage(pipelineDesc, shaderModule);
	initPrimitiveStage(pipelineDesc);
	initFragmentStage(pipelineDesc, shaderModule);
	initDepthStencilStage(pipelineDesc);
	initMultisampling(pipelineDesc);

	pipeline =
		wgpuDeviceCreateRenderPipeline(device.getDevice(), &pipelineDesc);

	wgpuShaderModuleRelease(shaderModule);
}

Pipeline::VertexBufferLayoutInfo Pipeline::getVertexBufferLayouts() {
	Pipeline::VertexBufferLayoutInfo info{};

	WGPUVertexBufferLayout vertexBufferLayout{};

	vertexAttributes.push_back(
		(WGPUVertexAttribute){.format = WGPUVertexFormat_Float32x2,
							  .offset = 0,
							  .shaderLocation = 0}); // position
	
	vertexAttributes.push_back(
		(WGPUVertexAttribute){.format = WGPUVertexFormat_Float32x3,
							  .offset = 0,
							  .shaderLocation = 1}); // color

	vertexBufferLayout.attributes = vertexAttributes.data();
	vertexBufferLayout.attributeCount = vertexAttributes.size();

	vertexBufferLayout.arrayStride = 5 * sizeof(float);
	vertexBufferLayout.stepMode = WGPUVertexStepMode_Vertex;

	info.layouts = vertexBufferLayout;
	info.count = 1;

	return info;
}

void Pipeline::initVertexStage(WGPURenderPipelineDescriptor &pipelineDesc,
							   WGPUShaderModule &shaderModule) {

	Pipeline::VertexBufferLayoutInfo vertexBufferLayout =
		getVertexBufferLayouts();

	pipelineDesc.vertex.bufferCount = vertexBufferLayout.count;
	pipelineDesc.vertex.buffers = &vertexBufferLayout.layouts;

	pipelineDesc.vertex.module = shaderModule;
	pipelineDesc.vertex.entryPoint = "vs_main";
	pipelineDesc.vertex.constantCount = 0;
	pipelineDesc.vertex.constants = nullptr;
}

void Pipeline::initPrimitiveStage(WGPURenderPipelineDescriptor &pipelineDesc) {
	pipelineDesc.primitive.topology =
		WGPUPrimitiveTopology::WGPUPrimitiveTopology_TriangleList;

	pipelineDesc.primitive.stripIndexFormat =
		WGPUIndexFormat::WGPUIndexFormat_Undefined;

	pipelineDesc.primitive.frontFace = WGPUFrontFace::WGPUFrontFace_CW;
	pipelineDesc.primitive.cullMode = WGPUCullMode::WGPUCullMode_None;
}

void Pipeline::initFragmentStage(WGPURenderPipelineDescriptor &pipelineDesc,
								 WGPUShaderModule &shaderModule) {
	WGPUFragmentState fragmenetState{};
	fragmenetState.module = shaderModule;
	fragmenetState.entryPoint = "fs_main";
	fragmenetState.constantCount = 0;
	fragmenetState.constants = nullptr;

	WGPUColorTargetState colorTarget = configureColorTarget();
	fragmenetState.targetCount = 1;
	fragmenetState.targets = &colorTarget;

	pipelineDesc.fragment = &fragmenetState;
}

void Pipeline::initDepthStencilStage(
	WGPURenderPipelineDescriptor &pipelineDesc) {

	pipelineDesc.depthStencil = nullptr;
}

void Pipeline::initMultisampling(WGPURenderPipelineDescriptor &pipelineDesc) {
	pipelineDesc.multisample.count = 1;
	pipelineDesc.multisample.mask = ~0u;
	pipelineDesc.multisample.alphaToCoverageEnabled = false;
}

WGPUColorTargetState Pipeline::configureColorTarget() {
	WGPUBlendState blendState{};

	// color
	blendState.color.srcFactor = WGPUBlendFactor::WGPUBlendFactor_SrcAlpha;
	blendState.color.dstFactor =
		WGPUBlendFactor::WGPUBlendFactor_OneMinusSrcAlpha;
	blendState.color.operation = WGPUBlendOperation::WGPUBlendOperation_Add;

	// alpha
	blendState.alpha.srcFactor = WGPUBlendFactor::WGPUBlendFactor_Zero;
	blendState.alpha.dstFactor = WGPUBlendFactor::WGPUBlendFactor_One;
	blendState.alpha.operation = WGPUBlendOperation::WGPUBlendOperation_Add;

	WGPUColorTargetState colorTarget{};

	WGPUSurfaceCapabilities capabilities = swapchain.getSurfaceCapabilities();

	colorTarget.format = capabilities.formats[0];
	colorTarget.blend = &blendState;
	colorTarget.writeMask = WGPUColorWriteMask::WGPUColorWriteMask_All;

	wgpuSurfaceCapabilitiesFreeMembers(capabilities);
	return colorTarget;
}

WGPUShaderModule Pipeline::createShaderModule(std::string path) {
	WGPUShaderModuleDescriptor shaderDesc;

	WGPUShaderModuleWGSLDescriptor shaderCodeDesc{};
	shaderCodeDesc.chain.next = nullptr;
	shaderCodeDesc.chain.sType = WGPUSType_ShaderModuleWGSLDescriptor;

	std::string shaderSource = readFile(path.c_str());
	shaderCodeDesc.code = shaderSource.c_str();

	shaderDesc.nextInChain = &shaderCodeDesc.chain;

	return wgpuDeviceCreateShaderModule(device.getDevice(), &shaderDesc);
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

} // namespace bingusengine
