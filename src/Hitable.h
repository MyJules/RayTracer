#pragma once

#include <Vector3.h>
#include <Ray.h>

#include <vector>
#include <algorithm>

class Hitalbe;

using HitableArr_t = std::vector<std::unique_ptr<Hitalbe>>;

struct HitRecord
{
    float t;
    Vec3_t p;
    Vec3_t normal;
};

class Hitalbe
{
public:
    virtual bool hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const = 0;
};