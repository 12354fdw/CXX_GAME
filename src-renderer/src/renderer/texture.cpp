#include "texture.hpp"
#include "webgpu/webgpu_cpp.h"

namespace bingusengine {

Texture::Texture(Device device, wgpu::TextureFormat format,
				 wgpu::TextureAspect textureAspect, wgpu::TextureUsage usage,
				 wgpu::Extent3D size, uint32_t mipLevelCount) {
	wgpu::TextureDescriptor textureDesc{};
	textureDesc.dimension = wgpu::TextureDimension::e2D;
	textureDesc.format = format;
	textureDesc.size = size;

	textureDesc.mipLevelCount = mipLevelCount;
	textureDesc.sampleCount = 1;

	textureDesc.usage = usage;
	textureDesc.viewFormatCount = 1;
	textureDesc.viewFormats = &format;

	rawTexture = device.getDevice().CreateTexture(&textureDesc);

	wgpu::TextureViewDescriptor viewDesc{};
	viewDesc.aspect = textureAspect;

	viewDesc.baseArrayLayer = 0;
	viewDesc.arrayLayerCount = 1;

	viewDesc.baseMipLevel = 0;
	viewDesc.mipLevelCount = mipLevelCount;

	viewDesc.dimension = wgpu::TextureViewDimension::e2D;
	viewDesc.format = format;

	textureView = rawTexture.CreateView(&viewDesc);
}

} // namespace bingusengine