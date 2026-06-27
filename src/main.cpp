#include <stdexcept>
#define WEBGPU_CPP_IMPLEMENTATION
#include <webgpu/webgpu-raii.hpp>

int main() {
	wgpu::InstanceDescriptor desc = {};
	desc.nextInChain = nullptr;

	wgpu::Instance instance = wgpu::createInstance(desc);
	if (!instance) {
		throw std::runtime_error("unable to create a webgpu instance!");
	}
	return 0;
}