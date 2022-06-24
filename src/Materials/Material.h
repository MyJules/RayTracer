#pragma once

#include <Ray.h>
#include <Hitable.h>
#include <Vector3.h>
#include <Renderer.h>

class Material
{
public:
    virtual bool scatter(const Ray &ray, const HitRecord &rec, Vec3_t &attenuation, Ray &scattered) const = 0;

protected:
    static Vec3_t reflect(const Vec3_t &v, const Vec3_t &n);
    static bool refract(const Vec3_t &v, const Vec3_t &n, float niOverNt, Vec3_t &refracter);
    static float schlick(float cosine, float refIdx);
};
