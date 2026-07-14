cmake_minimum_required(VERSION 3.20...3.30)

project(CXXGameClient LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE CLIENT_SOURCES
	"src/*.cpp"
	"src/*.hpp"
)

add_executable(cxxgame ${CLIENT_SOURCES})

target_link_libraries(cxxgame PRIVATE
	renderer
)