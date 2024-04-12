#include <cstring>

#include "M3L/Maths/Maths.hpp"
#include "M3L/Rendering/Target/RenderTarget3D.hpp"
#include "M3L/Rendering/PolyTri.hpp"

namespace m3l
{
    RenderTarget3D::~RenderTarget3D()
    {
        if (m_dib)
            DeleteObject(m_dib);
    }

    void RenderTarget3D::setCamera(const Camera &_cam)
    {
        m_cam = _cam;
    }

    const Camera &RenderTarget3D::getCamera() const
    {
        return m_cam;
    }

    Camera &RenderTarget3D::getCamera()
    {
        return m_cam;
    }

    void RenderTarget3D::setBpp(uint8_t _bpp)
    {
        m_bpp = _bpp;
    }

    uint8_t RenderTarget3D::getBpp() const
    {
        return m_bpp;
    }

    void RenderTarget3D::draw(const IDrawable3D &_elem, const Texture *_txtr)
    {
        _elem.draw(*this, _txtr);
    }

    void RenderTarget3D::create(uint32_t _x, uint32_t _y, const Camera &_cam, uint8_t _bpp)
    {
        m_cam = _cam;
        create(_x, _y, _bpp);
    }

    void RenderTarget3D::create(uint32_t _x, uint32_t _y, uint8_t _bpp)
    {
        HDC hdc = GetDC(NULL);
        BITMAPINFO bmi;

        m_bpp = _bpp;
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = _x;
        bmi.bmiHeader.biHeight = -static_cast<int32_t>(_y);
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = m_bpp;
        bmi.bmiHeader.biCompression = BI_RGB;
        if (m_dib)
            DeleteObject(m_dib);
        m_dib = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, reinterpret_cast<void **>(&m_data), NULL, 0);
        ReleaseDC(NULL, hdc);
        m_depth.clear();
        m_depth.resize(_x * _y, std::numeric_limits<float>::lowest());
    }

    void RenderTarget3D::clear(const Color &_clr)
    {
        uint32_t clr = CLR(_clr);
        size_t size = getSize().x * getSize().y * (m_bpp / 8);

        for (size_t it = 0; it < size; it += sizeof(uint32_t))
            std::memcpy(m_data + it, &clr, sizeof(uint32_t));
        std::fill(m_depth.begin(), m_depth.end(), std::numeric_limits<float>::lowest());
    }

    const uint8_t *RenderTarget3D::getData() const
    {
        return m_data;
    }

    // need strategy of Vertex link
    // need for size handling depending on strategy
    void RenderTarget3D::draw(const Vertex3D *_vtx, size_t _size, const Texture *_txtr)
    {
        std::vector<Vertex3D> vtx(_vtx, _vtx + _size);
        Point2<float> size = _txtr->getSize().as<float>();

        for (auto &_mvtx : vtx) {
            _mvtx.pos = m_cam.project(_mvtx.pos);
            _mvtx.txtrPos = _mvtx.txtrPos * size;
        }
        // caluclate minimal range of the drawing on y axes
        int32_t ystart = static_cast<int32_t>(std::max(std::min({ vtx[0].pos.y, vtx[1].pos.y, vtx[2].pos.y }), 0.f));
        int32_t yend = static_cast<int32_t>(std::min(std::max({ vtx[0].pos.y, vtx[1].pos.y, vtx[2].pos.y }), static_cast<float>(getSize().y)));

        for (; ystart < yend; ystart++)
            drawTriangle(vtx.data(), ystart, triRange(vtx.data(), ystart), _txtr);
    }

    void RenderTarget3D::drawTriangle(const Vertex3D *_vtx, int32_t _line, const Point2<uint32_t> &_range, const Texture *_txtr)
    {
        Point2<float> vertex1 = _vtx[0].pos.as2();
        Point2<float> vertex2 = _vtx[1].pos.as2();
        Point2<float> vertex3 = _vtx[2].pos.as2();

        float total_area = area(vertex1, vertex2, vertex3);

        // caluclate minimal range of the drawing on x axes
        float xstart = static_cast<float>(std::max(_range.x, 0U));
        float xend = static_cast<float>(std::min(_range.y, getSize().x));
        uint32_t depth_pos = _line * getSize().x + static_cast<uint32_t>(xstart);

        float ratio1 = 0.f;
        float ratio2 = 0.f;
        float ratio3 = 0.f;
        float depth = 0.f;
        Point2<float> rpos = { 0.f, 0.f };

        for (Point2<float> pos = { xstart, static_cast<float>(_line) }; pos.x <= xend; pos.x++, depth_pos++) {
            // calculating mapping of the depth
            ratio1 = area(vertex3, vertex1, pos) / total_area;
            ratio2 = area(vertex1, vertex2, pos) / total_area;
            ratio3 = 1 - ratio1 - ratio2;
            depth = _vtx[1].pos.z * ratio1 + _vtx[2].pos.z * ratio2 + _vtx[0].pos.z * ratio3;
            // check the depth on the pixel
            if (depth > m_depth[depth_pos]) {
                // calculating mapping of the texture
                rpos = _vtx[1].txtrPos * ratio1 + _vtx[2].txtrPos * ratio2 + _vtx[0].txtrPos * ratio3;
                setPixel(pos.as<uint32_t>(), _txtr->getPixel(rpos.as<uint32_t>()), depth);
            }
        }
    }

    void RenderTarget3D::setPixel(const Point2<uint32_t> &_pos, Color _clr, float _depth)
    {
        size_t pos = _pos.y * getSize().x + _pos.x;
        uint32_t clr = CLR(_clr);

        m_depth[pos] = _depth;
        std::memcpy(m_data + (_pos.y * getSize().x + _pos.x) * static_cast<uint32_t>(m_bpp / 8), &clr, sizeof(uint32_t));
    }
}