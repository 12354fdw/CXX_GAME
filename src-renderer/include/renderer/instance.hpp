#pragma once

#include "buffer.hpp"
#include "device.hpp"
#include "glm/ext/vector_float3.hpp"
#include "renderer/model.hpp"
#include "shaderStructs.hpp"
#include "webgpu/webgpu_cpp.h"
#include <vector>

namespace bingusengine {
namespace renderer {
class Instance {
  public:
	Instance(const Device &device, Model &model) : model(model), device(device) {
		std::vector<InstanceVertex> tmp = {{.tint = color}};
		instanceData.write(tmp);
	};

	glm::vec3 scale = glm::vec3(1, 1, 1);
	glm::vec3 rotation = glm::vec3(0, 0, 0);
	glm::vec3 position = glm::vec3(0, 0, 0);

	void setColor(glm::vec4 color) {
		this->color = color;
		std::vector<InstanceVertex> tmp = {{ .tint = color}};
		instanceData.write(tmp);
	};

	Model &getModel() { return model; };
	glm::vec4 getColor() { return color; };
	const Buffer<InstanceVertex> &getInstanceVertexBuffer() { return instanceData; };

  private:
	Model &model;
	const Device &device;

	Buffer<InstanceVertex> instanceData = Buffer<InstanceVertex>(
		device, wgpu::BufferUsage::Vertex | wgpu::BufferUsage::CopyDst, 1,
		"instance data");

	glm::vec4 color = glm::vec4(0.65f, 0.65f, 0.65f, 1.0f);
};

} // namespace renderer
} // namespace bingusengine
