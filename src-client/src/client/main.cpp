#include "renderer/instance.hpp"
#include "renderer/mesh.hpp"
#include "renderer/renderer.hpp"
#include <SDL3/SDL_events.h>
#include <cstdint>
#include <vector>


int main() {
	bingusengine::Renderer *renderer = new bingusengine::Renderer();

	std::vector<bingusengine::Vertex> vertexData = {
		{{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
		{{+0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
		{{+0.5f, +0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}},
		{{-0.5f, +0.5f, -0.5f}, {1.0f, 1.0f, 0.0f}},

		{{0.0f, 0.0f, +0.5f}, {1.0f, 0.0f, 1.0f}},
	};

	std::vector<uint32_t> indexData = {
		0, 2, 1, 0, 3, 2,

		0, 1, 4,
		1, 2, 4,
		2, 3, 4,
		3, 0, 4,
	};

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
