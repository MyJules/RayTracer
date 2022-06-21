#pragma once

#include <Ray.h>
#include <Vector3.h>
#include <Hitable.h>
#include <Camera.h>

using RayResult_t = Vec3_t;
using RenderResult_t = std::vector<RayResult_t>;

Vec3_t randomInUnitSphere();
Vec3_t color(const Ray &ray, const Hitables_t &world, int depth);
RenderResult_t render(const Camera &camera, const Hitables_t &scene, int width, int height, int ns);
RenderResult_t renderAsync(const Camera &camera, const Hitables_t &scene, int width, int height, int ns);