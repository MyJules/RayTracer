#pragma once

#include <Ray.h>
#include <Vector3.h>
#include <Hitable.h>

Vec3_t render(const Ray &ray, const HitableArr_t &world, int depth);
Vec3_t randomInUnitSphere();