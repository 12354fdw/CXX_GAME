#include "renderer/renderer.hpp"
#include "renderer/window.hpp"
#include <SDL3/SDL_events.h>


int main() {
	bingusengine::Renderer *renderer = new bingusengine::Renderer();

	SDL_Event event;
	bool running = true;
	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				running = false;
			}
		}
		renderer->renderFrame();
	}

	// i don't want to deal with a double free and also the OS already clears the memory when it exits
	delete renderer;

	return 0;
}