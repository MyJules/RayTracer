cmake_minimum_required(VERSION 3.0.0)
project(RayTracer VERSION 0.1.0)

include(CTest)
enable_testing()

set (CMAKE_CXX_STANDARD 17)

#good includes
include_directories(src)
include_directories(src/Hitable/)
include_directories(src/Materials/)

#add mathfu
set(mathfu_build_benchmarks OFF CACHE BOOL "")
set(mathfu_build_tests OFF CACHE BOOL "")
add_subdirectory(lib/mathfu mathfu)
include_directories(lib/mathfu/include)
include_directories(lib/mathfu/dependencies/vectorial/include)
include_directories(lib/thread-pool)
mathfu_configure_flags(RayTracer)

#add stb image
include_directories(lib/stb)

set(SrcFolder src)

#local libs
add_subdirectory(${SrcFolder}/)
add_subdirectory(${SrcFolder}/Hitable)
add_subdirectory(${SrcFolder}/Materials)

add_executable(RayTracer ${SrcFolder}/main.cpp)

target_link_libraries(RayTracer PUBLIC Source Hittable Materials)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
