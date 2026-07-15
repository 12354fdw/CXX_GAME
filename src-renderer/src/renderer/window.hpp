#pragma once
#include <SDL3/SDL_video.h>

namespace bingusengine {
class Window {
  public:
	Window();
	~Window();

	SDL_Window *getWindow() { return window; }
	float getAspectRatio();

  private:
	SDL_Window *window;
};

} // namespace bingusengine
