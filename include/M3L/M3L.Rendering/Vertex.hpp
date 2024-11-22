#pragma once

#include "M3L/Maths/Point3.hpp"
#include "M3L/Rendering/Color.hpp"

namespace m3l
{
    struct M3L_API Vertex2D
    {
        Point2<float> pos;
        Point2<float> txtrPos;
        Color clr = Color(0, 0, 0, 255);
    };

    struct M3L_API Vertex3D
    {
        Point3<float> pos;
        Point2<float> txtrPos;
        Color clr = Color(0, 0, 0, 255);
    };
}