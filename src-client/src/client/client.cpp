#include "client.hpp"
#include "glm/ext/vector_float3.hpp"
#include "renderer/camera.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_scancode.h>

namespace bingusengine {
namespace client {

Client::Client() {
	testInstance.position = glm::vec3(0, 0, -5);
	renderer.instances.push_back(testInstance);
}

void Client::tick(float dt) {
	processSDLEvents();

	moveCamera(dt);

	renderer.renderFrame();
}

void Client::moveCamera(float dt) {
	int numkeys;
	const bool *state = SDL_GetKeyboardState(&numkeys);

	SDL_PumpEvents();

	renderer::Camera &camera = renderer.camera;

	glm::vec3 forward = camera.direction;
	glm::vec3 up = camera.up;

	glm::vec3 right = glm::normalize(glm::cross(forward, up));

	float speed = state[SDL_SCANCODE_LSHIFT] ? 5 : 1;

	if (state[SDL_SCANCODE_W])
		camera.position += forward * speed * dt;

	if (state[SDL_SCANCODE_S])
		camera.position -= forward * speed * dt;

	if (state[SDL_SCANCODE_D])
		camera.position += right * speed * dt;

	if (state[SDL_SCANCODE_A])
		camera.position -= right * speed * dt;
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