#pragma once

#include "device.hpp"
#include <string>
#include <vector>

namespace bingusengine {

template <class T>
class Buffer {
  public:
	Buffer(const Device &device, WGPUBufferUsageFlags usageFlags, size_t byteSize,
		   std::string label = "unnamed buffer")
		: device(device) {
		capacity = byteSize;

		WGPUBufferDescriptor desc{};
		desc.label = label.c_str();
		desc.usage = usageFlags;
		desc.size = byteSize;
		desc.mappedAtCreation = false;

		rawBuffer = wgpuDeviceCreateBuffer(device.getDevice(), &desc);
	}

	~Buffer() { wgpuBufferRelease(rawBuffer); }

	void write(const std::vector<T> &data, uint32_t byteOffset = 0) {
		uint32_t byteSize = data.size() * sizeof(T);

		wgpuQueueWriteBuffer(
			device.getQueue(),
			this->rawBuffer, byteOffset, data.data(), byteSize);
	}

	const WGPUBuffer getRawBuffer() const { return rawBuffer; };
	size_t getCapacity() const { return capacity; }

  private:
	const Device &device;
	WGPUBuffer rawBuffer = nullptr;

	size_t capacity;
	WGPUBufferUsageFlags usageFlags;
};

} // namespace bingusengine
