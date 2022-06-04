cmake_minimum_required(VERSION 3.0.0)
project(RayTracer VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(src)

#add mathfu
set(mathfu_build_benchmarks OFF CACHE BOOL "")
set(mathfu_build_tests OFF CACHE BOOL "")
add_subdirectory(lib/mathfu mathfu)
include_directories(lib/mathfu/include)
include_directories(lib/mathfu/dependencies/vectorial/include)

set(SrcFolder src)

set(Src
${SrcFolder}/Ray.h
${SrcFolder}/Ray.cpp
${SrcFolder}/Vector3.h
${SrcFolder}/Hitable.h
${SrcFolder}/Sphere.h
${SrcFolder}/Sphere.cpp
${SrcFolder}/Renderer.h
${SrcFolder}/Renderer.cpp
${SrcFolder}/Camera.h
${SrcFolder}/Camera.cpp
${SrcFolder}/Material.h
)

add_executable(RayTracer ${SrcFolder}/main.cpp ${Src})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
