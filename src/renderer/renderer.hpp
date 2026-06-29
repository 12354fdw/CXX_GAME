#pragma once

#include "device.hpp"
#include "window.hpp"

namespace bingusengine {

class Renderer {
  public:
	Renderer();
	~Renderer();

  private:
	Window window;
	Device device;
};

} // namespace bingusengine
