#pragma once

#include <Vector3.h>
#include <Hitable.h>

#include <memory>

class Sphere : public Hitalbe
{
public:
    Sphere(){}
    Sphere(Vec3_t center, float r, std::shared_ptr<Material> material) : m_center(center), m_radius(r), m_material(material){};
    bool hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const override;

private:
    Vec3_t m_center;
    float m_radius;
    std::shared_ptr<Material> m_material;
};