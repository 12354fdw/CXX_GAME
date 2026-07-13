#include "renderer/renderer.hpp"
#include <SDL3/SDL_events.h>


int main() {
	bingusengine::Renderer *renderer = new bingusengine::Renderer();
	
	std::vector<float> vertexData = {-0.5, -0.5, +0.5, -0.5, +0.0, +0.5};
	renderer->getVertexBuffer().write(vertexData);

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

	delete renderer;

	return 0;
}