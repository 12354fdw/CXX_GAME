#pragma once

#include "renderer/device.hpp"
#include "webgpu/webgpu_cpp.h"

namespace bingusengine {
namespace renderer {
class Texture {
  public:
	Texture(Device device, wgpu::TextureFormat format,
			wgpu::TextureAspect textureAspect, wgpu::TextureUsage usage,
			wgpu::Extent3D size, uint32_t mipLevelCount = 1);

	~Texture() = default;

	wgpu::Texture getRawTexture() const { return rawTexture; };
	wgpu::TextureView getTextureView() const { return textureView; };

  private:
	wgpu::Texture rawTexture;
	wgpu::TextureView textureView;
};

} // namespace renderer
} // namespace bingusengine
