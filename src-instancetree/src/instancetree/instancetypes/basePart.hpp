#pragma once

#include "baseInstance.hpp"
#include "glm/ext/vector_float3.hpp"
#include "renderer/instance.hpp"

namespace bingusengine {
namespace instancetree {
namespace instancetypes {

class BasePart : BaseInstance {
  public:
	BasePart();
	~BasePart() override = default;

	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec3 scale = glm::vec3(1, 1, 1);

  private:
	bingusengine::renderer::Instance drawnInstance;
};

} // namespace instancetypes
} // namespace instancetree
} // namespace bingusengine
