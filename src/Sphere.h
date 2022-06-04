#pragma once

#include <Vector3.h>
#include <Hitable.h>

class Sphere : public Hitalbe
{
public:
    Sphere(){}
    Sphere(Vec3_t center, float r) : m_center(center), m_radius(r){};
    bool hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const override;

private:
    Vec3_t m_center;
    float m_radius;
};