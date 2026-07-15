#include "camera.hpp"

#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/geometric.hpp"
#include "glm/trigonometric.hpp"

namespace bingusengine {

glm::mat4 Camera::getMVPMatrix(Instance instance, float aspectRatio) {
	return getProjectionMatrix(aspectRatio) * getViewMatrix() *
		   getModelMatrix(instance);
}

glm::mat4 Camera::getModelMatrix(Instance instance) {
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, instance.position);

	model =
		glm::rotate(model, instance.rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	model =
		glm::rotate(model, instance.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	model =
		glm::rotate(model, instance.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));

	model = glm::scale(model, instance.scale);

	return model;
}

glm::mat4 Camera::getViewMatrix() {
	glm::vec3 target = position + glm::normalize(direction);
	return glm::lookAt(position, target, up);
}

glm::mat4 Camera::getProjectionMatrix(float aspectRatio) {
	return glm::perspective(glm::radians(FOV), aspectRatio, nearPlane, farPlane);
}

} // namespace bingusengine
