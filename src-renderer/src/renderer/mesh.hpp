#pragma once

#include "buffer.hpp"
#include "device.hpp"
#include "glm/ext/vector_float3.hpp"
#include <vector>

namespace bingusengine {

struct Vertex {
	glm::vec3 position;
	glm::vec3 color;
};

class Mesh {
  public:
	Mesh(const Device &device, std::vector<Vertex> &vertices,
		 std::vector<uint32_t> &indices);

	const Buffer<Vertex> &getVertexBuffer() const { return vertexBuffer; };
	const Buffer<uint32_t> &getIndexBuffer() const { return indexBuffer; };
	uint32_t getIndexCount() const { return indexCount; };

  private:
	Buffer<Vertex> vertexBuffer;
	Buffer<uint32_t> indexBuffer;

	uint32_t indexCount;
};

} // namespace bingusengine
