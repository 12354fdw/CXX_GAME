#include "mesh.hpp"
#include <cstdint>

namespace bingusengine {

Mesh::Mesh(const Device &device, std::vector<Vertex> &vertices,
		   std::vector<uint32_t> &indices)
	: vertexBuffer(device, WGPUBufferUsage_CopyDst | WGPUBufferUsage_Vertex,
				   vertices.size() * sizeof(Vertex), "vertex buffer"),
	  indexBuffer(device, WGPUBufferUsage_CopyDst | WGPUBufferUsage_Index,
				  indices.size() * sizeof(uint32_t), "index buffer"),
	  indexCount(indices.size()) {
	vertexBuffer.write(vertices);
	indexBuffer.write(indices);
}

} // namespace bingusengine

