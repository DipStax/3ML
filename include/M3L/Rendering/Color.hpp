#pragma once

#include <ostream>

#include "Tool/Export.hpp"

#define CLR(_clr)           ((static_cast<uint32_t>(_clr.A) << 24) | (static_cast<uint32_t>(_clr.B) << 16) | (static_cast<uint32_t>(_clr.G) << 8) | _clr.R)

#define CLR_GET_A(_clr)     ((_clr >> 24) & 0xFF)
#define CLR_GET_R(_clr)     ((_clr >> 8) & 0xFF)
#define CLR_GET_G(_clr)     ((_clr >> 16) & 0xFF)
#define CLR_GET_B(_clr)     ((_clr >> 24) & 0xFF)

#define CLR_GET_RGB(_clr)   (_clr & 0xFFFFFF)

#define CLR_SET_A(_clr, _a) _clr = ((((_a) & 0xFF) << 24) | CLR_GET_RGB(_clr))
#define CLR_SET_R(_clr, _r) _clr = (((_r) & 0xFF) | (_clr & 0xFFFFFF00))
#define CLR_SET_G(_clr, _g) _clr = ((((_g) & 0xFF) << 8) | (_clr & 0xFFFF00FF))
#define CLR_SET_B(_clr, _b) _clr = ((((_b) & 0xFF) << 16) | (_clr & 0xFF00FFFF))

#define CLR_RATIO(_v) (_v / 255)

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

    // [[nodiscard]] Color applyAlpha(const Color &_new, const Color &_old);
    [[nodiscard]] uint32_t applyAlpha(uint32_t _new, uint32_t _old);
}