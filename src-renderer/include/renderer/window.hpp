#pragma once
#include "webgpu/webgpu_cpp.h"
#include <SDL3/SDL_video.h>

namespace bingusengine {
namespace renderer {
class Window {
  public:
	Window();
	~Window();

	SDL_Window *getWindow() { return window; }
	float getAspectRatio();

	wgpu::Extent2D getWindowSize();

  private:
	SDL_Window *window;
};

} // namespace renderer
} // namespace bingusengine
