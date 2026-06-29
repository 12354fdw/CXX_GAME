#include "swapchain.hpp"
#include "device.hpp"
#include "sdl3webgpu.h"
#include "webgpu/webgpu.h"
#include "window.hpp"

namespace bingusengine {
Swapchain::Swapchain(Window &window, Device &device)
	: device(device), window(window) {
	surface = SDL_GetWGPUSurface(device.getInstance(), window.getWindow());
}

void Swapchain::configureSurface() {
	WGPUSurfaceConfiguration config{};
	config.nextInChain = nullptr;

	WGPUTextureFormat preferredFormat =
		wgpuSurfaceGetPreferredFormat(surface, device.getAdapter());
	config.format = preferredFormat;

	config.viewFormatCount = 0;
	config.viewFormats = nullptr;

	config.usage = WGPUTextureUsage_RenderAttachment;
	config.device = device.getDevice();

	config.presentMode = WGPUPresentMode_Fifo;
	config.alphaMode = WGPUCompositeAlphaMode_Auto;

	config.width = 640;
	config.height = 480;

	wgpuSurfaceConfigure(surface, &config);
}

void Swapchain::present() {
	auto [surfaceTexture, targetView] = getNextSurfaceViewData();
	if (!targetView)
		return;

	wgpuSurfacePresent(surface);
	wgpuTextureRelease(surfaceTexture.texture);
	wgpuTextureViewRelease(targetView);
}

std::pair<WGPUSurfaceTexture, WGPUTextureView>
Swapchain::getNextSurfaceViewData() {
	WGPUSurfaceTexture surfaceTexture;
	wgpuSurfaceGetCurrentTexture(surface, &surfaceTexture);

	if (surfaceTexture.status != WGPUSurfaceGetCurrentTextureStatus_Success) {
		return { surfaceTexture, nullptr };
	}

	WGPUTextureViewDescriptor viewDesc{};
	viewDesc.nextInChain = nullptr;
	viewDesc.label = "surface texture view";
	viewDesc.format = wgpuTextureGetFormat(surfaceTexture.texture);
	viewDesc.dimension = WGPUTextureViewDimension_2D;
	viewDesc.baseMipLevel = 0;
	viewDesc.mipLevelCount = 1;
	viewDesc.baseArrayLayer = 0;
	viewDesc.arrayLayerCount = 1;
	viewDesc.aspect = WGPUTextureAspect_All;

	WGPUTextureView targetView =
		wgpuTextureCreateView(surfaceTexture.texture, &viewDesc);

	return { surfaceTexture, targetView };
}

} // namespace bingusengine
