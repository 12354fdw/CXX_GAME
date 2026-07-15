#include "webgpu/webgpu.h"
#include <string>

namespace bingusengine {

[[nodiscard]] constexpr inline WGPUStringView
WSTR(const std::string &str) noexcept {
	return WGPUStringView{.data = str.c_str(), .length = str.size()};
}

} // namespace bingusengine
