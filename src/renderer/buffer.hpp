#pragma once

#include "device.hpp"
#include "webgpu/webgpu.h"
#include <vector>
namespace bingusengine {

template <class T>
class Buffer {
  public:
	Buffer(Device &device, std::vector<T> data, WGPUBufferUsageFlags usageFlags, std::string label = "unnamed buffer");
	~Buffer();

	void write(std::vector<T> data);

  private:
	Device &device;
	WGPUBuffer rawBuffer;

	WGPUBufferUsageFlags usageFlags;
};

} // namespace bingusengine
