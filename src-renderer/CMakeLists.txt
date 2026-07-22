cmake_minimum_required(VERSION 3.20...3.30)

project(CXXGameRenderer LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(DAWN_USE_WAYLAND ON)

find_package(SDL3 REQUIRED)
add_subdirectory(external/webgpu)
add_subdirectory(external/sdl3webgpu)
add_subdirectory(external/glm)

file(GLOB_RECURSE RENDERER_SOURCES
	"src/*.cpp"
	"include/*.hpp"
)

add_library(renderer STATIC ${RENDERER_SOURCES})

target_include_directories(renderer PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_include_directories(renderer PUBLIC
	external/
)

target_include_directories(renderer PRIVATE
	include/renderer
)

target_link_libraries(renderer PUBLIC
	webgpu
	SDL3::SDL3
	sdl3webgpu
	glm::glm-header-only
	$<$<BOOL:$<TARGET_EXISTS:sanitizerflags>>:sanitizerflags>
)