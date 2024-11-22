#include "M3L/Rendering/Target/BaseRenderWindow.hpp"

namespace m3l
{
    BaseRenderWindow::BaseRenderWindow(uint32_t _x, uint32_t _y, const std::string &_title)
        : Window(_x, _y, _title)
    {
        create(m_size.x, m_size.y);
        getCamera().setFov(110.f).setRange(0.1f, 100.f).setSize(static_cast<float>(m_size.x), static_cast<float>(m_size.y)).move({ 0, 0, -10 });
    }

    const Point2<uint32_t> &BaseRenderWindow::getSize() const
    {
        return m_size;
    }

    void BaseRenderWindow::display()
    {
        InvalidateRect(getWindow(), NULL, FALSE);
    }

    void BaseRenderWindow::clear(const Color &_clr)
    {
        RenderTarget3D::clear(_clr);
        RenderTarget2D::clear({ 0, 0, 0, 0 });
    }

    void BaseRenderWindow::create(uint32_t _x, uint32_t _y, const Camera &_cam, uint8_t _bpp)
    {
        m_size = { _x, _y };
        RenderTarget2D::create(m_size.x, m_size.y, _bpp);
        RenderTarget3D::create(m_size.y, m_size.x, _cam, _bpp);
    }

    void BaseRenderWindow::render(HDC _draw) const
    {
        Point2<uint32_t> size = getSize();
        BITMAPINFO bmi;
        std::vector<uint32_t> data(size.x * size.y);
        const uint32_t *data2d = reinterpret_cast<const uint32_t *>(RenderTarget2D::getData());
        const uint32_t *data3d = reinterpret_cast<const uint32_t *>(RenderTarget3D::getData());

        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = size.x;
        bmi.bmiHeader.biHeight = -static_cast<int32_t>(size.y);
        bmi.bmiHeader.biPlanes = 1;
        // resolve bpp diff on 2D and 3D RenderTarget
        bmi.bmiHeader.biBitCount = RenderTarget2D::getBpp();
        bmi.bmiHeader.biCompression = BI_RGB;
        for (size_t it = 0; it < size.x * size.y; it++) {
            // alpha is broken
            if (CLR_GET_ALPHA(data2d[it]) == 0)
                data[it] = data3d[it];
            else
                data[it] = data2d[it];
        }
        SetDIBitsToDevice(_draw, 0, 0, size.x, size.y, 0, 0, 0, size.y, data.data(), &bmi, DIB_RGB_COLORS);
    }
}