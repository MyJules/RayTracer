#pragma once

#include <Ray.h>
#include <Hitable.h>
#include <Vector3.h>
#include <Renderer.h>

static Vec3_t reflect(const Vec3_t &v, const Vec3_t &n);
static bool refract(const Vec3_t &v, const Vec3_t &n, float niOverNt, Vec3_t &refracter);
static float schlick(float cosine, float refIdx);

class Material
{
public:
    virtual bool scatter(const Ray &ray, const HitRecord &rec, Vec3_t &attenuation, Ray &scattered) const = 0;
};

class Lambertian : public Material
{
public:
    Lambertian(const Vec3_t &a) : m_albedo(a) {}
    bool scatter(const Ray &ray, const HitRecord &rec, Vec3_t &attenuation, Ray &scattered) const override;

private:
    Vec3_t m_albedo;
};

class Metal : public Material
{
public:
    Metal(const Vec3_t &a, float fuzz);
    bool scatter(const Ray &ray, const HitRecord &rec, Vec3_t &attenuation, Ray &scattered) const override;

private:
    Vec3_t m_albedo;
    float m_fuzz;
};

class Dielectric : public Material
{
public:
    Dielectric(float ri) : m_refIdx(ri) {}
    bool scatter(const Ray &ray, const HitRecord &rec, Vec3_t &attenuation, Ray &scattered) const override;

private:
    float m_refIdx;
};

Vec3_t reflect(const Vec3_t &v, const Vec3_t &n)
{
    return v - 2 * Vec3_t::DotProduct(v, n) * n;
}

bool refract(const Vec3_t &v, const Vec3_t &n, float niOverNt, Vec3_t &refracter)
{
    Vec3_t uv = v.Normalized();
    float dt = Vec3_t::DotProduct(uv, n);
    float discriminant = 1.0 - niOverNt * niOverNt * (1 - dt * dt);
    if (discriminant > 0)
    {
        refracter = Vec3_t(niOverNt) * (uv - n * Vec3_t(dt)) - n * Vec3_t(sqrt(discriminant));
        return true;
    }
    else
    {
        return false;
    }
}

float schlick(float cosine, float refIdx)
{
    float r0 = (1 - refIdx) / (1 + refIdx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}