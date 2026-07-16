#pragma once

#include "glm/ext/vector_float3.hpp"
#include "mesh.hpp"

namespace bingusengine {
namespace renderer {
class Instance {
  public:
	Instance(Mesh &mesh) : mesh(mesh) {};

	Mesh &getMesh() { return mesh; };

	glm::vec3 scale = glm::vec3(1, 1, 1);
	glm::vec3 rotation = glm::vec3(0, 0, 0);
	glm::vec3 position = glm::vec3(0, 0, 0);

  private:
	Mesh &mesh;
};

} // namespace renderer
} // namespace bingusengine
