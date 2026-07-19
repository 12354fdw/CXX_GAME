#pragma once

#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/vector_float3.hpp"

namespace bingusengine {
namespace renderer {

struct Vertex {
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 normal;
};

struct ImmediateData {
	glm::mat4 mvp;
	glm::vec3 color;
};

} // namespace renderer
} // namespace bingusengine