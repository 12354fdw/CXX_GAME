#include "renderer/instance.hpp"
#include "renderer/mesh.hpp"
#include "renderer/renderer.hpp"
#include <SDL3/SDL_events.h>
#include <cstdint>
#include <vector>


int main() {
	bingusengine::Renderer *renderer = new bingusengine::Renderer();

	std::vector<bingusengine::Vertex> vertexData = {
		{{-0.5, -0.5}, {1.0, 0.0, 0.0}},
		{{+0.5, -0.5}, {0.0, 1.0, 0.0}},
		{{+0.5, +0.5}, {0.0, 0.0, 1.0}},
		{{-0.5, +0.5}, {1.0, 0.0, 1.0}},
	};

	std::vector<uint32_t> indexData = {0, 1, 2, 0, 2, 3};
	bingusengine::Mesh mesh =
		bingusengine::Mesh(renderer->getDevice(), vertexData, indexData);
	
	bingusengine::Instance instance = bingusengine::Instance(mesh);

	
	renderer->instances.push_back(instance);

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
