#include "window.hpp"
#include "webgpu/webgpu_cpp.h"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>
#include <stdexcept>

namespace bingusengine {
namespace renderer {
Window::Window() {
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("webgpurenderer", 640, 480, SDL_WINDOW_RESIZABLE);
	if (!window) {
		throw std::runtime_error("unable to create a window!");
	}
}

Window::~Window() {
	SDL_DestroyWindow(window);
	SDL_Quit();
}

float Window::getAspectRatio() {
	wgpu::Extent2D windowSize = getWindowSize();
	return static_cast<float>(windowSize.width) / windowSize.height;
}

wgpu::Extent2D Window::getWindowSize() {
	int w, h;
	SDL_GetWindowSizeInPixels(window, &w, &h);

	return {static_cast<uint32_t>(w), static_cast<uint32_t>(h)};
}

} // namespace renderer
} // namespace bingusengine