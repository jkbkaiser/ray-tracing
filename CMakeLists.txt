cmake_minimum_required(VERSION 3.1.0...3.27.0)
project(raytracing LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCE
    src/color.h
    src/constants.h
    src/hittable.h
    src/hittable_list.h
    src/main.cc
    src/ray.h
    src/ray_tracing.h
    src/interval.h
    src/sphere.h
    src/vec3.h
)

include_directories(src)

message(STATUS "Compiler ID: " ${CMAKE_CXX_COMPILER_ID})
message(STATUS "Release flags: " ${CMAKE_CXX_FLAGS_RELEASE})
message(STATUS "Debug flags: " ${CMAKE_CXX_FLAGS_DEBUG})

add_compile_options(-Wnon-virtual-dtor)     # Class has virtual functions, but its destructor is not virtual
add_compile_options(-Wreorder)              # Data member will be initialized after [other] data member
add_compile_options(-Wmaybe-uninitialized)  # Variable improperly initialized
add_compile_options(-Wunused-variable)      # Variable is defined but unused

add_executable(raytracer ${SOURCE})
