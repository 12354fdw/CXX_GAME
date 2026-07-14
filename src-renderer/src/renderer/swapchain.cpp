#include "swapchain.hpp"
#include "device.hpp"
#include "webgpu/webgpu.h"
#include <SDL3/SDL_video.h>
#include <iostream>

namespace bingusengine {
Swapchain::Swapchain(Device &device, Window &window, WGPUSurface &surface)
	: device(device), window(window), surface(surface) {}

Swapchain::~Swapchain() {}

void Swapchain::configureSurface() {
	std::cout << "reconfiguring surface" << std::endl;
	
	WGPUSurfaceConfiguration config{};
	config.nextInChain = nullptr;

	WGPUSurfaceCapabilities capabilities = getSurfaceCapabilities();
	config.format = capabilities.formats[0];

	config.viewFormatCount = 0;
	config.viewFormats = nullptr;

	config.usage = WGPUTextureUsage_RenderAttachment;
	config.device = device.getDevice();

	config.presentMode = WGPUPresentMode_Fifo;
	config.alphaMode = WGPUCompositeAlphaMode_Auto;

	int w, h;
	SDL_GetWindowSize(window.getWindow(), &w, &h);

	config.width = w;
	config.height = h;

	wgpuSurfaceConfigure(surface, &config);
	wgpuSurfaceCapabilitiesFreeMembers(capabilities);
}

WGPUSurfaceCapabilities Swapchain::getSurfaceCapabilities() {
	WGPUSurfaceCapabilities capabilities{};
	wgpuSurfaceGetCapabilities(surface, device.getAdapter(), &capabilities);

	return capabilities;
}

std::pair<WGPUSurfaceTexture, WGPUTextureView>
Swapchain::getNextSurfaceViewData() {
	WGPUSurfaceTexture surfaceTexture;
	wgpuSurfaceGetCurrentTexture(surface, &surfaceTexture);

	if (surfaceTexture.status != WGPUSurfaceGetCurrentTextureStatus_Success) {
		configureSurface();
		return {surfaceTexture, nullptr};
	}

	WGPUTextureViewDescriptor viewDesc{};
	viewDesc.nextInChain = nullptr;
	viewDesc.label = "surface texture view";
	viewDesc.format = WGPUTextureFormat_Undefined;
	viewDesc.dimension = WGPUTextureViewDimension_2D;
	viewDesc.baseMipLevel = 0;
	viewDesc.mipLevelCount = 1;
	viewDesc.baseArrayLayer = 0;
	viewDesc.arrayLayerCount = 1;
	viewDesc.aspect = WGPUTextureAspect_All;

	WGPUTextureView targetView =
		wgpuTextureCreateView(surfaceTexture.texture, &viewDesc);

	return {surfaceTexture, targetView};
}

} // namespace bingusengine
