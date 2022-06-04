#pragma once

#include <Vector3.h>

class Ray
{
public:
    Ray(){}
    Ray(const Vec3_t &a, const Vec3_t &b)
    {
        m_a = a;
        m_b = b;
    }
    Vec3_t origin() const { return m_a; }
    Vec3_t direction() const { return m_b; }
    Vec3_t pointAtParameter(Vec3_v t) const {return m_a + t*m_b;}

private:
    Vec3_t m_a;
    Vec3_t m_b;
};