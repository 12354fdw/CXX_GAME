#pragma once

#include "device.hpp"
#include "utils.hpp"
#include <string>
#include <vector>

namespace bingusengine {
namespace renderer {
template <class T> class Buffer {
  public:
	Buffer(const Device &device, wgpu::BufferUsage usageFlags, size_t elementSize,
		   std::string label = "unnamed buffer")
		: device(device) {
		capacity = elementSize * sizeof(T);

		wgpu::BufferDescriptor desc{};
		desc.label = WSTR(label);
		desc.usage = usageFlags;
		desc.size = elementSize;
		desc.mappedAtCreation = false;

		rawBuffer = device.getDevice().CreateBuffer(&desc);
	}

	~Buffer() {}

	void write(const std::vector<T> &data, uint32_t byteOffset = 0) {
		uint32_t byteSize = data.size() * sizeof(T);

		device.getQueue().WriteBuffer(rawBuffer, byteOffset, data.data(),
									  byteSize);
	}

	const wgpu::Buffer &getRawBuffer() const { return rawBuffer; };
	size_t getCapacity() const { return capacity; }

  private:
	const Device &device;
	wgpu::Buffer rawBuffer = nullptr;

	size_t capacity;
};

} // namespace renderer
} // namespace bingusengine
