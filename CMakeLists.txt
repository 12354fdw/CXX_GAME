cmake_minimum_required(VERSION 3.20...3.30)

project(CXXGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(
    -Wno-error
    -Wno-c2y-extensions
)
add_subdirectory(webgpu)

find_package(SDL3 REQUIRED)

add_executable(cxxgame
src/main.cpp
src/renderer/device.cpp
src/renderer/window.cpp
)

target_link_libraries(cxxgame PRIVATE
	webgpu
	SDL3::SDL3
)