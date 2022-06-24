#pragma once

#include <Material.h>

class Metal : public Material
{
public:
    Metal(const Vec3_t &a, float fuzz);
    bool scatter(const Ray &ray, const HitRecord &rec, Vec3_t &attenuation, Ray &scattered) const override;

private:
    Vec3_t m_albedo;
    float m_fuzz;
};