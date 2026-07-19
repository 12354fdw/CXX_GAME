#include "client.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/ext/vector_float4.hpp"
#include "renderer/camera.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_scancode.h>

namespace bingusengine {
namespace client {

Client::Client() {
	testInstance.position = glm::vec3(0, 0, -5);

	floor.position = glm::vec3(0.0f, -2.0f, 0.0f);
	floor.scale = glm::vec3(100, 1, 100);

	floor.setColor(glm::vec4(0.0f, 0.7f, 0.0f, 1.0f));

	glass.position = glm::vec3(1.0f, 0.0f, 0.0f);
	glass.scale = glm::vec3(1.0f, 1, 0.1);
	glass.setColor(glm::vec4(0.435, 0.752, 1.0, 0.5f));

	renderer.instances.push_back(testInstance);
	renderer.instances.push_back(floor);
	renderer.instances.push_back(glass);
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