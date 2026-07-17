#include "model.hpp"
#include "renderer/mesh.hpp"
#include <stdexcept>
#include <vector>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

namespace bingusengine {
namespace renderer {

Model::Model(const Device &device, std::string objPath) {
	tinyobj::ObjReaderConfig readerConf;
	tinyobj::ObjReader reader;

	if (!reader.ParseFromFile(objPath, readerConf)) {
		throw std::runtime_error("unable to find mesh file!");
	}

	auto &attrib = reader.GetAttrib();
	auto &shapes = reader.GetShapes();

	for (const auto &shape : shapes) {
		const tinyobj::mesh_t &mesh = shape.mesh;

		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;

		for (size_t i = 0; i < mesh.indices.size(); i++) {
			tinyobj::index_t idx = mesh.indices[i];

			float vx = attrib.vertices[3 * idx.vertex_index + 0];
			float vy = attrib.vertices[3 * idx.vertex_index + 1];
			float vz = attrib.vertices[3 * idx.vertex_index + 2];

			vertices.push_back({{vx, vy, vz}, {0.5f, 0.5f, 0.5f}});

			indices.push_back(static_cast<uint32_t>(i));
		}

		this->meshes.emplace_back(device, vertices, indices);
	}
}

} // namespace renderer
} // namespace bingusengine