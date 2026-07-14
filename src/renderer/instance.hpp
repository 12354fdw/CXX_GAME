#pragma once

#include "mesh.hpp"

namespace bingusengine {

class Instance {
  public:
	Instance(Mesh &mesh) : mesh(mesh) {};

	Mesh &getMesh() { return mesh; };

  private:
	Mesh &mesh;
};

} // namespace bingusengine
