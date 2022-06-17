#pragma once

#include <Ray.h>
#include <Vector3.h>
#include <Renderer.h>
#include <Hitable.h>

static Vec3_t reflect(const Vec3_t &v, const Vec3_t &n)
{
    return v - 2 * Vec3_t::DotProduct(v, n) * n;
}

static bool refract(const Vec3_t &v, const Vec3_t &n, float niOverNt, Vec3_t &refracter)
{
    Vec3_t uv = v.Normalized();
    float dt = Vec3_t::DotProduct(uv, n);
    float discriminant = 1.0 - niOverNt*niOverNt*(1-dt*dt);
    if(discriminant > 0)
    {
        refracter = Vec3_t(niOverNt) * (uv - n * Vec3_t(dt)) - n * Vec3_t(sqrt(discriminant));
        return true;
    }else
    {
        return false;
    }
}

static float schlick(float cosine, float refIdx)
{
    float r0 = (1-refIdx) / (1+refIdx);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1-cosine), 5);
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
    Metal(const Vec3_t &a, float fuzz) : m_albedo(a)
    { 
        if(fuzz < 1) 
        {
            m_fuzz = fuzz;
        }
        else
        { 
            m_fuzz = 1;
        }
    }
    
    bool scatter(const Ray &ray, const HitRecord &rec, Vec3_t &attenuation, Ray &scattered) const override
    {
        Vec3_t reflected = reflect(ray.direction().Normalized(), rec.normal);
        scattered = Ray(rec.p, reflected + Vec3_t(m_fuzz) * randomInUnitSphere());
        attenuation = m_albedo;
        return Vec3_t::DotProduct(scattered.direction(), rec.normal) > 0;
    }

private:
    Vec3_t m_albedo;
    float m_fuzz;
};

class Dielectric : public Material 
{
public:
    Dielectric(float ri) : m_refIdx(ri){}

    bool scatter(const Ray &ray, const HitRecord &rec, Vec3_t &attenuation, Ray &scattered) const override
    {
        Vec3_t outwardNormal;
        Vec3_t reflected = reflect(ray.direction(), rec.normal);
        float niOverNt;
        attenuation = Vec3_t(1.0, 1.0, 1.0);
        Vec3_t refracter;
        float reflectProb;
        float cosine;
        if(Vec3_t::DotProduct(ray.direction(), rec.normal) > 0)
        {
            outwardNormal = -rec.normal;
            niOverNt = m_refIdx;
            cosine = m_refIdx * Vec3_t::DotProduct(ray.direction(), rec.normal) / ray.direction().Length();
        }else
        {
            outwardNormal = rec.normal;
            niOverNt = 1.0 / m_refIdx;
            cosine = -Vec3_t::DotProduct(ray.direction(), rec.normal) / ray.direction().Length();
        }

        if(refract(ray.direction(), outwardNormal, niOverNt, refracter))
        {
            reflectProb = schlick(cosine, m_refIdx);
        }else
        {
            scattered = Ray(rec.p, reflected);
            reflectProb = 1.0;
        }

        if(drand48() < reflectProb)
        {
            scattered = Ray(rec.p, reflected);
        }else
        {
            scattered = Ray(rec.p, refracter);
        }

        return true;
    }

private:
    float m_refIdx;
};