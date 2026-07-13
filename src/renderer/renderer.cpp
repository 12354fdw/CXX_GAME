#include "renderer.hpp"
#include "dawn/dawn_proc_table.h"
#include "device.hpp"
#include "pipeline.hpp"
#include "sdl3webgpu.h"
#include "swapchain.hpp"
#include "window.hpp"

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

	// set vertex buffer
	wgpuRenderPassEncoderSetVertexBuffer(renderPassEncoder, 0,
										 vertexBuffer.getRawBuffer(), 0,
										 vertexBuffer.getCapacity());

	// draw call
	wgpuRenderPassEncoderDraw(renderPassEncoder, 3, 1, 0, 0);

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
