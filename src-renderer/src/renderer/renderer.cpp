#include "renderer.hpp"
#include "buffer.hpp"
#include "device.hpp"
#include "instance.hpp"
#include "mesh.hpp"
#include "pipeline.hpp"
#include "sdl3webgpu.hpp"
#include "swapchain.hpp"
#include "webgpu/webgpu_cpp.h"
#include "window.hpp"
#include <cstdint>

namespace bingusengine {

Renderer::Renderer()
	: window(), device(window),
	  surface(SDL_GetWGPUSurface(device.getInstance(), window.getWindow())),
	  swapchain(device, window, surface), mainPipeline(device, swapchain) {
	swapchain.configureSurface();
}

Renderer::~Renderer() {
	surface.Unconfigure();
}

void Renderer::renderFrame() {

	wgpu::CommandEncoder encoder = createCommandEncoder();

	auto [surfaceTexture, targetView] = swapchain.getNextSurfaceViewData();
	if (!targetView)
		return;

	wgpu::RenderPassDescriptor renderPassDesc{};
	renderPassDesc.nextInChain = nullptr;

	// background color
	wgpu::RenderPassColorAttachment renderPassColorAttachment = {};

	renderPassColorAttachment.view = targetView;
	renderPassColorAttachment.resolveTarget = nullptr;
	renderPassColorAttachment.depthSlice = wgpu::kDepthSliceUndefined;

	renderPassColorAttachment.loadOp = wgpu::LoadOp::Clear;
	renderPassColorAttachment.storeOp = wgpu::StoreOp::Store;
	renderPassColorAttachment.clearValue = wgpu::Color{0.435, 0.752, 1.0, 1.0};

	// end of background color

	renderPassDesc.colorAttachmentCount = 1;
	renderPassDesc.colorAttachments = &renderPassColorAttachment;

	wgpu::RenderPassEncoder renderPassEncoder =
		encoder.BeginRenderPass(&renderPassDesc);

	// set pipeline
	renderPassEncoder.SetPipeline(mainPipeline.getPipeline());

	for (auto &instance : instances) {
		const Mesh &mesh = instance.getMesh();
		const Buffer<Vertex> &vertexBuffer = mesh.getVertexBuffer();
		const Buffer<uint32_t> &indexBuffer = mesh.getIndexBuffer();

		// vertex buffer
		renderPassEncoder.SetVertexBuffer(0, vertexBuffer.getRawBuffer(), 0,
										  vertexBuffer.getCapacity());

		// index buffer
		renderPassEncoder.SetIndexBuffer(mesh.getIndexBuffer().getRawBuffer(),
										wgpu::IndexFormat::Uint32, 0,
										indexBuffer.getCapacity());

		// draw call
		renderPassEncoder.DrawIndexed(mesh.getIndexCount(), 1, 0, 0, 0);
	}

	renderPassEncoder.End();

	// command buffer!
	wgpu::CommandBufferDescriptor cmdBufferDesc{};
	cmdBufferDesc.nextInChain = nullptr;
	cmdBufferDesc.label = "frame cmd buffer";

	wgpu::CommandBuffer cmdBuffer = encoder.Finish(&cmdBufferDesc);

	// submit it!
	device.submitCommandBuffer(cmdBuffer);

	// present
	surface.Present();
}

wgpu::CommandEncoder Renderer::createCommandEncoder() {
	wgpu::CommandEncoderDescriptor desc{};
	desc.nextInChain = nullptr;
	desc.label = "frame command encoder";

	return device.getDevice().CreateCommandEncoder(&desc);
}

} // namespace bingusengine
