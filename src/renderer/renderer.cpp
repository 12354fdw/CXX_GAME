#include "renderer.hpp"
#include "device.hpp"
#include "window.hpp"

namespace bingusengine {

Renderer::Renderer() : window(), device(window) {}

Renderer::~Renderer() {}

} // namespace bingusengine
