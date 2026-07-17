#pragma once

#include "renderer/renderer.hpp"

namespace bingusengine {
namespace client {
class Client {
  public:
	Client();

	void tick(float dt);

	bingusengine::renderer::Renderer renderer =
		bingusengine::renderer::Renderer();

  private:
};

} // namespace client
} // namespace bingusengine
