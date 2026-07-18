#include "client.hpp"
#include <SDL3/SDL_events.h>

namespace bingusengine {
namespace client {

Client::Client() {
	testInstance.position = glm::vec3(0, 0, -5);
	renderer.instances.push_back(testInstance);
}

void Client::tick(double dt) {
	processSDLEvents();

	renderer.renderFrame();
}

void Client::processSDLEvents() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT) {
			running = false;
		}
	}
}

} // namespace client
} // namespace bingusengine