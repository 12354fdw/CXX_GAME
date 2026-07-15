#pragma once

#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/vector_float3.hpp"
#include "renderer/instance.hpp"

namespace bingusengine {

class Camera {
  public:
	const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	Camera() {};

	float FOV = 60;
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f);

	glm::mat4 getMVPMatrix(Instance instance, float aspectRatio);

	float nearPlane = 0.1f;
	float farPlane = 100.0f;

  private:
	glm::mat4 getModelMatrix(Instance instance);
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix(float aspectRatio);
};

} // namespace bingusengine
