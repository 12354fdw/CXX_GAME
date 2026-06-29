#include "renderer.hpp"
#include "device.hpp"
#include "swapchain.hpp"
#include "webgpu/webgpu.h"
#include "window.hpp"

namespace bingusengine {

Renderer::Renderer() : window(), device(window), swapchain(window, device) {}

Renderer::~Renderer() { wgpuSurfaceUnconfigure(surface); }

void Renderer::renderFrame() {
	swapchain.present();
}

} // namespace bingusengine
