#pragma once
#include <SDL3/SDL_video.h>

namespace renderer {
class Window {
  public:
	Window();
	~Window();

  private:
	SDL_Window *window;
};

} // namespace renderer
