#include "renderer.hpp"
#include "buffer.hpp"
#include "device.hpp"
#include "instance.hpp"
#include "mesh.hpp"
#include "pipeline.hpp"
#include "sdl3webgpu.h"
#include "swapchain.hpp"
#include "webgpu/webgpu.h"
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
	wgpuSurfaceUnconfigure(surface);
	wgpuSurfaceRelease(surface);
}

void Renderer::renderFrame() {

	WGPUCommandEncoder encoder = createCommandEncoder();

	auto [surfaceTexture, targetView] = swapchain.getNextSurfaceViewData();
	if (!targetView)
		return;

	WGPURenderPassDescriptor renderPassDesc{};
	renderPassDesc.nextInChain = nullptr;

	// background color
	WGPURenderPassColorAttachment renderPassColorAttachment = {};

	renderPassColorAttachment.view = targetView;
	renderPassColorAttachment.resolveTarget = nullptr;
	renderPassColorAttachment.depthSlice =
		WGPU_DEPTH_SLICE_UNDEFINED;

	renderPassColorAttachment.loadOp = WGPULoadOp_Clear;
	renderPassColorAttachment.storeOp = WGPUStoreOp_Store;
	renderPassColorAttachment.clearValue = WGPUColor{0.435, 0.752, 1.0, 1.0};

	// end of background color

	renderPassDesc.colorAttachmentCount = 1;
	renderPassDesc.colorAttachments = &renderPassColorAttachment;

	WGPURenderPassEncoder renderPassEncoder =
		wgpuCommandEncoderBeginRenderPass(encoder, &renderPassDesc);

	// set pipeline
	wgpuRenderPassEncoderSetPipeline(renderPassEncoder,
									 mainPipeline.getPipeline());

	for (auto &instance : instances) {
		const Mesh &mesh = instance.getMesh();
		const Buffer<Vertex> &vertexBuffer = mesh.getVertexBuffer();
		const Buffer<uint32_t> &indexBuffer = mesh.getIndexBuffer();

		// vertex buffer
		wgpuRenderPassEncoderSetVertexBuffer(
			renderPassEncoder, 0, vertexBuffer.getRawBuffer(), 0,
			vertexBuffer.getCapacity());

		// index buffer
		wgpuRenderPassEncoderSetIndexBuffer(
			renderPassEncoder, mesh.getIndexBuffer().getRawBuffer(),
			WGPUIndexFormat_Uint32, 0, indexBuffer.getCapacity());

		// draw call
		wgpuRenderPassEncoderDrawIndexed(renderPassEncoder, mesh.getIndexCount(), 1, 0, 0, 0);
	}

	wgpuRenderPassEncoderEnd(renderPassEncoder);
	wgpuRenderPassEncoderRelease(renderPassEncoder);

	// command buffer!
	WGPUCommandBufferDescriptor cmdBufferDesc{};
	cmdBufferDesc.nextInChain = nullptr;
	cmdBufferDesc.label = "frame cmd buffer";

	WGPUCommandBuffer cmdBuffer =
		wgpuCommandEncoderFinish(encoder, &cmdBufferDesc);
	
	// submit it!
	device.submitCommandBuffer(cmdBuffer);

	wgpuCommandEncoderRelease(encoder);
	wgpuCommandBufferRelease(cmdBuffer);

	// present
	wgpuSurfacePresent(surface);

	wgpuTextureRelease(surfaceTexture.texture);
	wgpuTextureViewRelease(targetView);
}

WGPUCommandEncoder Renderer::createCommandEncoder() {
	WGPUCommandEncoderDescriptor desc{};
	desc.nextInChain = nullptr;
	desc.label = "frame command encoder";

	return wgpuDeviceCreateCommandEncoder(device.getDevice(), &desc);
}

} // namespace bingusengine
