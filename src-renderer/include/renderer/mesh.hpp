#pragma once

#include "buffer.hpp"
#include "device.hpp"
#include "shaderStructs.hpp"
#include <vector>

namespace bingusengine {
namespace renderer {

class Mesh {
  public:
	Mesh(const Device &device, std::vector<Vertex> &vertices,
		 std::vector<uint32_t> &indices);

	const GPUBuffer<Vertex> &getVertexBuffer() const { return vertexBuffer; };
	const GPUBuffer<uint32_t> &getIndexBuffer() const { return indexBuffer; };
	uint32_t getIndexCount() const { return indexCount; };

  private:
	GPUBuffer<Vertex> vertexBuffer;
	GPUBuffer<uint32_t> indexBuffer;

	uint32_t indexCount;
};

} // namespace renderer
} // namespace bingusengine
