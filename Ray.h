#pragma once

#include "Vector3.h"

class Ray
{
public:
    Ray(){}
    Ray(const Vector3_t &a, const Vector3_t &b)
    {
        m_a = a;
        m_b = b;
    }
    Vector3_t origin() const { return m_a; }
    Vector3_t direction() const { return m_b; }
    Vector3_t pointAtParameter(Vector3_v t) const {return m_a + t*m_b;}

private:
    Vector3_t m_a;
    Vector3_t m_b;
};