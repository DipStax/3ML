#pragma once

#include <ostream>

#include "Tool/Export.hpp"

#define CLR(_clr)           (static_cast<uint32_t>(_clr.A) << 24) | (static_cast<uint32_t>(_clr.B) << 16) | (static_cast<uint32_t>(_clr.G) << 8) | _clr.R
#define CLR_GET_ALPHA(_clr) ((_clr >> 24) & 0xFF)
#define CLR_GET_RGB(_clr)   (_clr & 0xFFFFFF)

namespace m3l
{
    struct M3L_API Color
    {
        uint8_t R = 0;
        uint8_t G = 0;
        uint8_t B = 0;
        uint8_t A = 255;
    };

    M3L_API std::ostream &operator<<(std::ostream &_os, const Color &_clr);
}