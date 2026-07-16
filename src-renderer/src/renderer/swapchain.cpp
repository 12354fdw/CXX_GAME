#include "swapchain.hpp"
#include "device.hpp"
#include "webgpu/webgpu_cpp.h"
#include <SDL3/SDL_video.h>
#include <iostream>

namespace bingusengine {
namespace renderer {
Swapchain::Swapchain(Device &device, Window &window, wgpu::Surface &surface)
	: device(device), window(window), surface(surface) {}

Swapchain::~Swapchain() {}

void Swapchain::configureSurface() {
	std::cout << "reconfiguring surface" << std::endl;

	wgpu::SurfaceConfiguration config{};
	config.nextInChain = nullptr;

	wgpu::SurfaceCapabilities capabilities = getSurfaceCapabilities();
	config.format = capabilities.formats[0];

	config.viewFormatCount = 0;
	config.viewFormats = nullptr;

	config.usage = wgpu::TextureUsage::RenderAttachment;
	config.device = device.getDevice();

	config.presentMode = wgpu::PresentMode::Fifo;
	config.alphaMode = wgpu::CompositeAlphaMode::Auto;

	int w, h;
	SDL_GetWindowSize(window.getWindow(), &w, &h);

	config.width = w;
	config.height = h;

	surface.Configure(&config);
}

wgpu::SurfaceCapabilities Swapchain::getSurfaceCapabilities() {
	wgpu::SurfaceCapabilities capabilities{};
	surface.GetCapabilities(device.getAdapter(), &capabilities);

	return capabilities;
}

std::pair<wgpu::SurfaceTexture, wgpu::TextureView>
Swapchain::getNextSurfaceViewData() {
	wgpu::SurfaceTexture surfaceTexture;
	surface.GetCurrentTexture(&surfaceTexture);

	if (surfaceTexture.status !=
			wgpu::SurfaceGetCurrentTextureStatus::SuccessOptimal &&
		surfaceTexture.status !=
			wgpu::SurfaceGetCurrentTextureStatus::SuccessSuboptimal) {
		configureSurface();
		return {surfaceTexture, nullptr};
	}

	wgpu::TextureViewDescriptor viewDesc{};
	viewDesc.nextInChain = nullptr;
	viewDesc.label = "surface texture view";
	viewDesc.format = wgpu::TextureFormat::Undefined;
	viewDesc.dimension = wgpu::TextureViewDimension::e2D;
	viewDesc.baseMipLevel = 0;
	viewDesc.mipLevelCount = 1;
	viewDesc.baseArrayLayer = 0;
	viewDesc.arrayLayerCount = 1;
	viewDesc.aspect = wgpu::TextureAspect::All;

	wgpu::TextureView targetView = surfaceTexture.texture.CreateView(&viewDesc);

	return {surfaceTexture, targetView};
}

} // namespace renderer
} // namespace bingusengine
