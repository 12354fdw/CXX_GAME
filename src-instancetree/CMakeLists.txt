cmake_minimum_required(VERSION 3.20...3.30)

project(CXXGameInstancetree LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE INSTANCETREE_SOURCES
	"src/*.cpp"
	"src/*.hpp"
)

add_library(instancetree STATIC ${INSTANCETREE_SOURCES})

target_include_directories(instancetree PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

target_link_libraries(cxxgame PUBLIC

)