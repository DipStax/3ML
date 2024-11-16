#pragma once

#include <functional>
#include <windows.h>
#include <string>

#include "M3L/Maths/Point2.hpp"
#include "M3L/Rendering/Color.hpp"

#define EXT(_path) _path.substr(_path.rfind(".") + 1)

namespace m3l
{
    class M3L_API Image
    {
        public:
            Image() = default;
            ~Image();

            void load(const std::string &_path);
            void load(const uint8_t *_data, const Point2<uint32_t> &_size, uint8_t _bpp = 32);

            [[nodiscard]] Point2<uint32_t> getSize() const;
            [[nodiscard]] Color getPixel(const Point2<uint32_t> &_pos) const;

        private:
            friend class RenderTarget;

            void facBmp(const std::string &_path);

            HBITMAP m_bmp = NULL;
            uint8_t m_bpp = 0;
            std::vector<uint8_t> m_pxl;
            Point2<uint32_t> m_size = { 0, 0 };
    };
}