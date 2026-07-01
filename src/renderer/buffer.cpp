#include "buffer.hpp"
#include "webgpu/webgpu.h"
#include <vector>

namespace bingusengine {

template <typename T>
Buffer<T>::Buffer(Device &device, std::vector<T> data,
						WGPUBufferUsageFlags usageFlags,
						std::string label)
	: device(device), usageFlags(usageFlags) {

	WGPUBufferDescriptor desc{};
	desc.label = label.c_str();
	desc.usage = usageFlags;
	desc.size = data.size();
	desc.mappedAtCreation = false;

	rawBuffer = wgpuDeviceCreateBuffer(device.getDevice(), &desc);
}

template <> Buffer<class T>::~Buffer() { wgpuBufferRelease(rawBuffer); }

template <typename T> void Buffer<T>::write(std::vector<T> data) {
	wgpuQueueWriteBuffer(device.getQueue(), rawBuffer, 0, data.data(), data.size());
}

} // namespace bingusengine

