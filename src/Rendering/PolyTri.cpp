#include "M3L/Rendering/PolyTri.hpp"
#include "M3L/Maths/Maths.hpp"

namespace m3l
{
    std::vector<std::array<Vertex2D, 3>> polyTri(const Vertex2D *_vtx, size_t _size)
    {
        std::vector<std::array<Vertex2D, 3>> res;
        CircleList<Vertex2D> cl;

        for (size_t it = 0; it < _size; it++)
            cl.push_back(_vtx[it]);
        for (int32_t it = 0; cl.size() > 3;) {
            if (priv::isEarTip(cl, it)) {
                res.push_back({ cl[it - 1], cl[it], cl[it + 1] });
                cl.erase(it);
            } else {
                it++;
            }
        }
        res.push_back({ cl[-1], cl[0], cl[1] });
        return res;
    }

    Point2<uint32_t> triRange(const Vertex2D *_vtx, int32_t _line)
    {
        Point2<float> res;
        bool first = false;
        float clres = 0;

        for (size_t it = 0; it < 3; it++) {
            if (_vtx[it].pos.y == _line && _line == _vtx[it + 1].pos.y) {
                res = { std::min(_vtx[it].pos.x, _vtx[(it + 1) % 3].pos.x), std::max(_vtx[it].pos.x, _vtx[(it + 1) % 3].pos.x) };
                break;
            } else if ((_vtx[it].pos.y <= _line && _line <= _vtx[(it + 1) % 3].pos.y) ||
                (_vtx[(it + 1) % 3].pos.y <= _line && _line <= _vtx[it].pos.y)) {
                clres = _vtx[it].pos.x;

                if (_vtx[(it + 1) % 3].pos.x != _vtx[it].pos.x) {
                    float slope = (_vtx[(it + 1) % 3].pos.y - _vtx[it].pos.y) / (_vtx[(it + 1) % 3].pos.x - _vtx[it].pos.x);
                    clres = (static_cast<float>(_line) - (_vtx[it].pos.y - slope * _vtx[it].pos.x)) / slope;
                }
                if (!first) {
                    res.x = clres;
                    first = true;
                } else {
                    res.y = clres;
                }
            }
        }
        if (res.x > res.y)
            std::swap(res.x, res.y);
        return res.as<uint32_t>();
    }

    Point2<uint32_t> triRange(const Vertex3D *_vtx, int32_t _line)
    {
        Point2<float> res;
        bool first = false;
        float clres = 0;

        for (size_t it = 0; it < 3; it++) {
            if (_vtx[it].pos.y == _line && _line == _vtx[it + 1].pos.y) {
                res = { std::min(_vtx[it].pos.x, _vtx[(it + 1) % 3].pos.x), std::max(_vtx[it].pos.x, _vtx[(it + 1) % 3].pos.x) };
                break;
            } else if ((_vtx[it].pos.y <= _line && _line <= _vtx[(it + 1) % 3].pos.y) ||
                (_vtx[(it + 1) % 3].pos.y <= _line && _line <= _vtx[it].pos.y)) {
                clres = _vtx[it].pos.x;

                if (_vtx[(it + 1) % 3].pos.x != _vtx[it].pos.x) {
                    float slope = (_vtx[(it + 1) % 3].pos.y - _vtx[it].pos.y) / (_vtx[(it + 1) % 3].pos.x - _vtx[it].pos.x);
                    clres = (static_cast<float>(_line) - (_vtx[it].pos.y - slope * _vtx[it].pos.x)) / slope;
                }
                if (!first) {
                    res.x = clres;
                    first = true;
                }
                else {
                    res.y = clres;
                }
            }
        }
        if (res.x > res.y)
            std::swap(res.x, res.y);
        return res.as<uint32_t>();
    }

    namespace priv
    {
        bool isEarTip(const CircleList<Vertex2D> &_cl, int32_t _start)
        {
            float size = area(_cl[_start - 1].pos, _cl[_start].pos, _cl[_start + 1].pos);
            float inside = 0;
            int32_t elem = static_cast<int32_t>(_cl.size());

            if (reflex(_cl[_start - 1].pos, _cl[_start].pos, _cl[_start + 1].pos))
                return false;
            for (int32_t it = _start + 2; it < _start + elem - 2; it++) {
                inside = calInside(_cl[it].pos, _cl[_start - 1].pos, _cl[_start].pos, _cl[_start + 1].pos);
                if (size - 1 < inside && inside < size + 1)
                    return false;
            }
            return true;
        }

        float calInside(const Point2<float> &_pt, const Point2<float>& _a, const Point2<float> &_b, const Point2<float>& _c)
        {
            return area(_pt, _b, _c) + area(_a, _pt, _c) + area(_a, _b, _pt);
        };

        bool reflex(const Point2<float> _prev, const Point2<float> &_cur, const Point2<float> &_next)
        {
            Point2<float> cp = _cur - _prev;
            Point2<float> nc = _next - _cur;

            return (cp.x * nc.y - cp.y * nc.x) < 0;
        }
    }
}

