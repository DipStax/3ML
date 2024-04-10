#include <cstring>

#include "M3L/Rendering/RenderTarget2D.hpp"
#include "M3L/Rendering/PolyTri.hpp"
#include "M3L/Maths/Maths.hpp"

namespace m3l
{
    RenderTarget2D::~RenderTarget2D()
    {
        if (m_dib)
            DeleteObject(m_dib);
    }

    void RenderTarget2D::setBpp(uint8_t _bpp)
    {
        m_bpp = _bpp;
    }

    uint8_t RenderTarget2D::getBpp() const
    {
        return m_bpp;
    }

    void RenderTarget2D::draw(const IDrawable2D & _elem, const Texture *_txtr)
    {
        _elem.draw(*this, _txtr);
    }

    void RenderTarget2D::draw(const Vertex2D *_vtx, size_t _size, const Texture * _txtr)
    {
        Point2<int32_t> min;
        Point2<int32_t> max;

        if (_size > 3) {
            for (const auto &_tri : polyTri(_vtx, _size))
                draw(_tri.data(), 3, _txtr);
        } else {
            // caluclate minimal range of the drawing on y axes
            int32_t ystart = static_cast<int32_t>(std::max(std::min({ _vtx[0].pos.y, _vtx[1].pos.y, _vtx[2].pos.y }), 0.f));
            int32_t yend = static_cast<int32_t>(std::min(std::max({ _vtx[0].pos.y, _vtx[1].pos.y, _vtx[2].pos.y }), static_cast<float>(getSize().y)));

            for (; ystart < yend; ystart++)
                drawTriangle(_vtx, ystart, triRange(_vtx, ystart), _txtr);
        }
    }

    void RenderTarget2D::draw(const Vertex2D *_vtx, size_t _size, VertexArray::Type _type)
    {
        if (_type == VertexArray::Type::Point) {
            for (size_t it = 0; it < _size; it++)
                setPixel(_vtx[it].pos.as<uint32_t>(), _vtx[it].clr);
        } else if (_type == VertexArray::Type::Lines || _type == VertexArray::Type::LineStrip) {
            for (size_t it = 1; it < _size; it++)
                drawLine(_vtx[it - 1], _vtx[it]);
            if (_type == VertexArray::Type::LineStrip)
                drawLine(_vtx[_size - 1], _vtx[0]);
        } else if (_type == VertexArray::Type::Polygone) {
            if (_size > 3) {
                for (const auto &_tri : polyTri(_vtx, _size))
                    draw(_tri.data(), 3, _type);
            } else {
                // caluclate minimal range of the drawing on y axes
                int32_t ystart = static_cast<int32_t>(std::max(std::min({ _vtx[0].pos.y, _vtx[1].pos.y, _vtx[2].pos.y }), 0.f));
                int32_t yend = static_cast<int32_t>(std::min(std::max({ _vtx[0].pos.y, _vtx[1].pos.y, _vtx[2].pos.y }), static_cast<float>(getSize().y)));

                for (; ystart < yend; ystart++)
                    drawTriangle(_vtx, ystart, triRange(_vtx, ystart));
            }
        }
    }

    void RenderTarget2D::create(uint32_t _x, uint32_t _y, uint8_t _bpp)
    {
        HDC hdc = GetDC(NULL);
        BITMAPINFO bmi;

        m_bpp = _bpp;
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = _x;
        bmi.bmiHeader.biHeight = -static_cast<int32_t>(_y);
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biCompression = BI_RGB;
        if (m_dib)
            DeleteObject(m_dib);
        m_dib = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, reinterpret_cast<void **>(&m_data), NULL, 0);
        ReleaseDC(NULL, hdc);
    }

    void RenderTarget2D::clear(const Color &_clr)
    {
        uint32_t clr = CLR(_clr);
        size_t size = getSize().x * getSize().y * (m_bpp / 8);

        for (size_t it = 0; it < size; it += sizeof(uint32_t))
            std::memcpy(m_data + it, &clr, sizeof(uint32_t));
    }

    const uint8_t *RenderTarget2D::getData() const
    {
        return m_data;
    }

    void RenderTarget2D::drawLine(const Vertex2D &_start, const Vertex2D &_end)
    {
        Point2<uint32_t> derivate = (_end.pos - _start.pos).as<uint32_t>();
        uint32_t endx = static_cast<uint32_t>(_end.pos.x);
        uint32_t delta = 2 * derivate.y - derivate.x;

        for (Point2<uint32_t> pos = _start.pos.as<uint32_t>(); pos.x < endx; pos.x++) {
            setPixel(pos, { 0, 0, 0, 255 });
            if (delta > 0) {
                pos.y++;
                delta -= 2 * derivate.x;
            }
            delta += 2 * derivate.y;
        }
    }

    void RenderTarget2D::drawTriangle(const Vertex2D *_vtx, int32_t _line, const Point2<uint32_t> &_range, const Texture * _txtr)
    {
        Point2<float> pos;
        float total_area = area(_vtx[0].pos, _vtx[1].pos, _vtx[2].pos);
        float ratio1 = 0;
        float ratio2 = 0;
        float ratio3 = 0;
        Point2<uint32_t> size = getSize() - 1;

        // caluclate minimal range of the drawing on x axes
        float xstart = static_cast<float>(std::max(_range.x, 0U));
        float xend = static_cast<float>(std::min(_range.y, size.x));

        for (Point2<float> px = { xstart, static_cast<float>(_line) }; px.x <= xend; px.x++) {
            // calculating mapping of the texture
            ratio1 = area(_vtx[2].pos, _vtx[0].pos, px) / total_area;
            ratio2 = area(_vtx[0].pos, _vtx[1].pos, px) / total_area;
            ratio3 = 1 - ratio1 - ratio2;
            pos = _vtx[1].txtrPos * ratio1 + _vtx[2].txtrPos * ratio2 + _vtx[0].txtrPos * ratio3;
            // px position is assured by calculation the minimal range in x and y axes;
            setPixel(px.as<uint32_t>(), _txtr->getPixel(pos.as<uint32_t>()));
        }
    }

    void RenderTarget2D::drawTriangle(const Vertex2D *_vtx, int32_t _line, const Point2<uint32_t> &_range)
    {
        Point2<float> pos;
        float total_area = area(_vtx[0].pos, _vtx[1].pos, _vtx[2].pos);
        float ratio1 = 0;
        float ratio2 = 0;
        float ratio3 = 0;
        Color clr = { 0, 0, 0, 0 };
        Point2<uint32_t> size = getSize() - 1;

        // caluclate minimal range of the drawing on x axes
        float xstart = static_cast<float>(std::max(_range.x, 0U));
        float xend = static_cast<float>(std::min(_range.y, size.x));

        for (Point2<float> px = { xstart, static_cast<float>(_line) }; px.x <= xend; px.x++) {
            // calculating mapping of the texture
            ratio1 = area(_vtx[2].pos, _vtx[0].pos, px) / total_area;
            ratio2 = area(_vtx[0].pos, _vtx[1].pos, px) / total_area;
            ratio3 = 1 - ratio1 - ratio2;
            clr.R = _vtx[1].clr.R * ratio1 + _vtx[2].clr.R * ratio2 + _vtx[0].clr.R * ratio3;
            clr.G = _vtx[1].clr.G * ratio1 + _vtx[2].clr.G * ratio2 + _vtx[0].clr.G * ratio3;
            clr.B = _vtx[1].clr.B * ratio1 + _vtx[2].clr.B * ratio2 + _vtx[0].clr.B * ratio3;
            clr.A = _vtx[1].clr.A * ratio1 + _vtx[2].clr.A * ratio2 + _vtx[0].clr.A * ratio3;
            setPixel(px.as<uint32_t>(), clr);
        }
    }

    void RenderTarget2D::setPixel(const Point2<uint32_t> &_pos, Color _clr)
    {
        uint32_t clr = CLR(_clr);

        std::memcpy(m_data + (_pos.y * getSize().x + _pos.x) * static_cast<uint32_t>(m_bpp / 8), &clr, sizeof(uint32_t));
    }
}