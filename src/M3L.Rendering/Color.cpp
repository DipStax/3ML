#include "M3L/Rendering/Color.hpp"

namespace m3l
{
    std::ostream &operator<<(std::ostream &_os, const Color &_clr)
    {
        _os << "{ " << static_cast<uint16_t>(_clr.R) << ", " << static_cast<uint16_t>(_clr.G)
            << ", " << static_cast<uint16_t>(_clr.B) << ", " << static_cast<uint16_t>(_clr.A) << " }";
        return _os;
    }
}