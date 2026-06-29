#include "renderer/device.hpp"
#include "renderer/window.hpp"
#include <SDL3/SDL_events.h>

int main() {
	renderer::Window window = renderer::Window();
	renderer::Device device = renderer::Device();

	SDL_Event event;
	bool running = true;
	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				running = false;
			}
		}
	}

	return 0;
}