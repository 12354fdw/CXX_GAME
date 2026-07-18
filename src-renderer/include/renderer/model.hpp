#pragma once

#include "renderer/device.hpp"
#include "renderer/mesh.hpp"
#include <vector>

namespace bingusengine {
namespace renderer {

class Model {
  public:
	Model(const Device &device, std::string objPath);

	const std::vector<Mesh> &getMeshes() { return meshes; };

  private:
	std::vector<Mesh> meshes;
};

} // namespace renderer
} // namespace bingusengine