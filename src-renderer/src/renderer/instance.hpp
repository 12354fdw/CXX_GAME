#pragma once

#include "glm/ext/vector_float3.hpp"
#include "mesh.hpp"

namespace bingusengine {

class Instance {
  public:
	Instance(Mesh &mesh) : mesh(mesh) {};

	Mesh &getMesh() { return mesh; };

	glm::vec3 scale;
	glm::vec3 rotation;
	glm::vec3 position;

  private:
	Mesh &mesh;
};

} // namespace bingusengine
