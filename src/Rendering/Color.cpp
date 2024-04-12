#include "M3L/Rendering/Color.hpp"

namespace m3l
{
    std::ostream &operator<<(std::ostream &_os, const Color &_clr)
    {
        _os << "{ " << static_cast<uint16_t>(_clr.R) << ", " << static_cast<uint16_t>(_clr.G)
            << ", " << static_cast<uint16_t>(_clr.B) << ", " << static_cast<uint16_t>(_clr.A) << " }";
        return _os;
    }

    // Color applyAlpha(const Color &_new, const Color &_old)
    // {
    //     Color clr{};
    //     float old_alpha = _old.A / 255;
    //     float new_alpha = _new.A / 255;
    //     float new_ratio = new_alpha / clr.A;
    //     float old_ratio = old_alpha * (1 - new_alpha) / clr.A;

    //     clr.A = 1 - (1 - old_alpha) * (1 - new_alpha);
    //     clr.R = _new.R * new_ratio + (_old.R * old_ratio);
    //     clr.G = _new.G * new_ratio + (_old.G * old_ratio);
    //     clr.B = _new.B * new_ratio + (_old.B * old_ratio);
    //     return clr;
    // }

    uint32_t applyAlpha(uint32_t _new, uint32_t _old)
    {
        uint32_t clr{};
        float old_alpha = CLR_RATIO(CLR_GET_A(_old));
        float new_alpha = CLR_RATIO(CLR_GET_A(_new));

        CLR_SET_A(clr, static_cast<uint8_t>((1 - (1 - old_alpha) * (1 - new_alpha)) * 255.f));
        float new_ratio = new_alpha / CLR_RATIO(CLR_GET_A(clr));
        float old_ratio = old_alpha * (1 - new_alpha) / CLR_RATIO(CLR_GET_A(clr));

        CLR_SET_R(clr, static_cast<uint8_t>(CLR_GET_R(_new) * new_ratio + CLR_GET_R(_old) * old_ratio));
        CLR_SET_G(clr, static_cast<uint8_t>(CLR_GET_G(_new) * new_ratio + CLR_GET_G(_old) * old_ratio));
        CLR_SET_B(clr, static_cast<uint8_t>(CLR_GET_B(_new) * new_ratio + CLR_GET_B(_old) * old_ratio));
        return clr;
    }
}