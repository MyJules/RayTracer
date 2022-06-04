#pragma once

#include <Vector3.h>
#include <Ray.h>

class Camera
{
public:
    Camera();

    Ray getRay(Vec3_v u, Vec3_v v);
    
    Vec3_t origin;
    Vec3_t lowerLeftCorner;
    Vec3_t horizontal;
    Vec3_t vertical;
};

