cmake_minimum_required(VERSION 3.20...3.30)

project(CXXGame LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(
    -Wno-error
    -Wno-c2y-extensions
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND NOT MSVC)
    add_library(sanitizerflags INTERFACE)
    
    target_compile_options(sanitizerflags INTERFACE
        -fsanitize=address
        -fsanitize=undefined
        -fno-omit-frame-pointer
        -g
        -O0
    )
    
    target_link_options(sanitizerflags INTERFACE
        -fsanitize=address
        -fsanitize=undefined
    )
endif()

add_subdirectory(src-renderer)
add_subdirectory(src-client)