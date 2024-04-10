#include <exception>
#include <map>

#include "M3L/Rendering/Image.hpp"

namespace m3l
{
    Image::~Image()
    {
        if (m_bmp != NULL)
            DeleteObject(m_bmp);
    }

    void Image::load(const std::string &_path)
    {
        using facFn = void (Image::*)(const std::string&);

        static std::map<std::string, facFn> fac = {
            { "bmp", &Image::facBmp }
        };
        std::string ext = EXT(_path);

        if (fac.contains(ext))
            (this->*fac[ext])(_path);
        else
            throw std::runtime_error("Unable to load the image");
    }

    void Image::load(const uint8_t *_data, const Point2<uint32_t> &_size, uint8_t _bpp)
    {
        size_t size = _size.x * _size.y * (_bpp / 8);

        m_bpp = _bpp;
        if (m_bmp != NULL)
            DeleteObject(m_bmp);
        m_pxl.resize(size);
        for (size_t it = 0; it < size; it++)
            m_pxl[it] = _data[it];
        m_size = _size;
    }

    Point2<uint32_t> Image::getSize() const
    {
        return m_size;
    }

    Color Image::getPixel(const Point2<uint32_t>& _pos) const
    {
        uint32_t pos = (_pos.y * getSize().x + _pos.x) * (m_bpp / 8);
        return Color{ m_pxl.at(pos + 2), m_pxl.at(pos + 1), m_pxl.at(pos), m_pxl.at(pos + 3) };
    }

    void Image::facBmp(const std::string &_path)
    {
        BITMAP bmp;
        BITMAPINFO bmpInfo;
        HDC hdc;

        m_bmp = (HBITMAP)LoadImageA(NULL, _path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        GetObject(m_bmp, sizeof(BITMAP), &bmp);
        hdc = CreateCompatibleDC(NULL);
        SelectObject(hdc, m_bmp);
        ZeroMemory(&bmpInfo, sizeof(BITMAPINFO));
        bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmpInfo.bmiHeader.biWidth = bmp.bmWidth;
        bmpInfo.bmiHeader.biHeight = bmp.bmHeight;
        bmpInfo.bmiHeader.biPlanes = 1;
        bmpInfo.bmiHeader.biBitCount = bmp.bmBitsPixel;
        bmpInfo.bmiHeader.biCompression = BI_RGB;
        m_size = { static_cast<uint32_t>(bmp.bmWidth), static_cast<uint32_t>(bmp.bmHeight) };
        m_bpp = bmp.bmBitsPixel;
        m_pxl.resize(m_size.x * m_size.y * m_bpp); // correct calculatation of bpp (32)
        GetDIBits(hdc, m_bmp, 0, bmp.bmHeight, m_pxl.data(), &bmpInfo, DIB_RGB_COLORS);
        DeleteDC(hdc);
    }
}