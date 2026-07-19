#pragma once

#include "renderer/instance.hpp"
#include "renderer/model.hpp"
#include "renderer/renderer.hpp"

namespace bingusengine {
namespace client {
class Client {
  public:
	Client();

	bool running = true;

	void tick(float dt);

	bingusengine::renderer::Renderer renderer =
		bingusengine::renderer::Renderer();

  private:
	renderer::Model testModel = renderer::Model(
		renderer.getDevice(), "./assets/primitiveMeshes/cube.obj");

	renderer::Instance testInstance = renderer::Instance(testModel);
	renderer::Instance floor = renderer::Instance(testModel);

	void moveCamera(float dt);
	void processSDLEvents();
};

} // namespace client
} // namespace bingusengine
