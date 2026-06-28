#pragma once

#include "webgpu/webgpu.h"
#define WEBGPU_CPP_IMPLEMENTATION
#include <webgpu/webgpu_cpp.h>

namespace renderer {
class Device {
  public:
	Device();
	~Device();

  private:
	WGPUInstance instance;
	WGPUAdapter adapter;

	void createInstance();
	void getAdapter();
};

}