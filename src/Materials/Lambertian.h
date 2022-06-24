#pragma once

#include <Material.h>

class Lambertian : public Material
{
public:
    Lambertian(const Vec3_t &a) : m_albedo(a) {}
    bool scatter(const Ray &ray, const HitRecord &rec, Vec3_t &attenuation, Ray &scattered) const override;

private:
    Vec3_t m_albedo;
};