#pragma once

#include <Ray.h>
#include <Vector3.h>
#include <Renderer.h>
#include <Hitable.h>

static Vec3_t reflect(const Vec3_t &v, const Vec3_t &n)
{
    return v - 2 * Vec3_t::DotProduct(v, n) * n;
}

class Material
{
public:
    virtual bool scatter(const Ray &ray, const HitRecord &rec, Vec3_t &attenuation, Ray &scattered) const = 0;
};

class Lambertian : public Material
{
public:
    Lambertian(const Vec3_t &a) : m_albedo(a){}
    bool scatter(const Ray &ray, const HitRecord &rec, Vec3_t &attenuation, Ray &scattered) const override
    {
        Vec3_t target = rec.p + rec.normal + randomInUnitSphere();
        scattered = Ray(rec.p, target-rec.p);
        attenuation = m_albedo;
        return true;
    }

private:
    Vec3_t m_albedo;
};

class Metal : public Material
{
public:
    Metal(const Vec3_t &a) : m_albedo(a){}
    
    bool scatter(const Ray &ray, const HitRecord &rec, Vec3_t &attenuation, Ray &scattered) const override
    {
        Vec3_t reflected = reflect(ray.direction().Normalized(), rec.normal);
        scattered = Ray(rec.p, reflected);
        attenuation = m_albedo;
        return Vec3_t::DotProduct(scattered.direction(), rec.normal) > 0;
    }

private:
    Vec3_t m_albedo;
};