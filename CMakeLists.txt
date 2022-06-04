cmake_minimum_required(VERSION 3.0.0)
project(RayTracer VERSION 0.1.0)

include(CTest)
enable_testing()

#add mathfu
set(mathfu_build_benchmarks OFF CACHE BOOL "")
set(mathfu_build_tests OFF CACHE BOOL "")
add_subdirectory(lib/mathfu mathfu)
include_directories(lib/mathfu/include)
include_directories(lib/mathfu/dependencies/vectorial/include)

set(Src 
Ray.h
Ray.cpp
Vector3.h)

add_executable(RayTracer main.cpp ${Src})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
