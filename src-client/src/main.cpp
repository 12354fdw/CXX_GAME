#include "client/client.hpp"
#include "glm/ext/vector_float3.hpp"
#include "renderer/instance.hpp"
#include "renderer/model.hpp"
#include "renderer/renderer.hpp"
#include <SDL3/SDL_events.h>
#include <vector>

int main() {
	bingusengine::client::Client client = bingusengine::client::Client();

	bingusengine::renderer::Model model =
		bingusengine::renderer::Model(client.renderer.getDevice(), "./assets/primitiveMeshes/cube.obj");

	bingusengine::renderer::Instance instance =
		bingusengine::renderer::Instance(model);
	
	instance.position = glm::vec3(0, 0, -5);

	client.renderer.instances.push_back(instance);

	SDL_Event event;
	bool running = true;
	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				running = false;
			}
		}
		client.renderer.renderFrame();
	}

	return 0;
}
