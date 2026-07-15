#include "window.hpp"
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_video.h>
#include <stdexcept>

namespace bingusengine {
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
	float min = 0.0f;
	float max = 100.0f;
	return SDL_GetWindowAspectRatio(window, &min, &max);
}

} // namespace bingusengine