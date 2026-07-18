#include "client.hpp"
#include <SDL3/SDL_events.h>
#include <chrono>

int main() {
	bingusengine::client::Client client = bingusengine::client::Client();

	auto lastTime = std::chrono::steady_clock::now();

	while (client.running) {
		auto currentTime = std::chrono::steady_clock::now();
		std::chrono::duration<double> dt = currentTime - lastTime;

		client.tick(dt.count());
		lastTime = currentTime;
	}

	return 0;
}
