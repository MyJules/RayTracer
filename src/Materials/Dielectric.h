#pragma once

#include <Material.h>

class Dielectric : public Material
{
public:
    Dielectric(float ri) : m_refIdx(ri) {}
    bool scatter(const Ray &ray, const HitRecord &rec, Vec3_t &attenuation, Ray &scattered) const override;

private:
    float m_refIdx;
};