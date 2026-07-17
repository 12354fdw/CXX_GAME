#pragma once

#include "glm/ext/vector_float3.hpp"
#include "renderer/model.hpp"

namespace bingusengine {
namespace renderer {
class Instance {
  public:
	Instance(Model &model) : model(model) {};

	Model &getModel() { return model; };

	glm::vec3 scale = glm::vec3(1, 1, 1);
	glm::vec3 rotation = glm::vec3(0, 0, 0);
	glm::vec3 position = glm::vec3(0, 0, 0);

  private:
	Model &model;
};

} // namespace renderer
} // namespace bingusengine
