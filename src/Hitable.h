#pragma once

#include <Ray.h>
#include <Vector3.h>

#include <vector>
#include <algorithm>
#include <memory>

class Material;

class Hitalbe;

using HitableArr_t = std::vector<std::unique_ptr<Hitalbe>>;

struct HitRecord
{
    float t;
    Vec3_t p;
    Vec3_t normal;
    std::shared_ptr<Material> material;
};

class Hitalbe
{
public:
    Hitalbe() = default;
    virtual ~Hitalbe() = default;
    
    virtual bool hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const = 0;
};