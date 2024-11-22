#pragma once

#include <array>
#include <vector>

#include "M3L/Container/CircleList.hpp"
#include "M3L/Rendering/Vertex.hpp"

namespace m3l
{
    M3L_API std::vector<std::array<Vertex2D, 3>> polyTri(const Vertex2D *_vtx, size_t _size);
    M3L_API Point2<uint32_t> triRange(const Vertex2D *_vtx, int32_t _line);
    M3L_API Point2<uint32_t> triRange(const Vertex3D* _vtx, int32_t _line);

    namespace priv
    {
        M3L_API bool isEarTip(const CircleList<Vertex2D> &_cl, int32_t _start);
        M3L_API float calInside(const Point2<float> &_pt, const Point2<float>& _a, const Point2<float> &_b, const Point2<float>& _c);
        M3L_API bool reflex(const Point2<float> _prev, const Point2<float> &_cur, const Point2<float> &_next);
    }
}