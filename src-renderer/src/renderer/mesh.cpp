#include "mesh.hpp"
#include <cstdint>

namespace bingusengine {
namespace renderer {

Mesh::Mesh(const Device &device, std::vector<Vertex> &vertices,
		   std::vector<uint32_t> &indices)
	: vertexBuffer(device,
				   wgpu::BufferUsage::CopyDst | wgpu::BufferUsage::Vertex,
				   vertices.size(), "vertex buffer"),
	  indexBuffer(device, wgpu::BufferUsage::CopyDst | wgpu::BufferUsage::Index,
				  indices.size(), "index buffer"),
	  indexCount(indices.size()) {
	vertexBuffer.write(vertices);
	indexBuffer.write(indices);
}

} // namespace renderer
} // namespace bingusengine
