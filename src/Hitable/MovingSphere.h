#pragma once

#include <Hitable.h>

class MovingSphere : public Hitalbe
{
public:
    MovingSphere() {}
    MovingSphere(Vec3_t center1, Vec3_t center2, float time1, float time2, float radius, std::shared_ptr<Material> material);
    bool hit(const Ray &ray, float tMin, float tMax, HitRecord &record) const override;

private:
    Vec3_t center(float time) const;


private:
    Vec3_t m_center1;
    Vec3_t m_center2;
    float m_time1;
    float m_time2;
    float m_radius;
    std::shared_ptr<Material> m_material;
};
