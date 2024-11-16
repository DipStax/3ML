#include "M3L/Core/Mouse.hpp"

namespace m3l
{
    Point2<uint32_t> Mouse::Position()
    {
        LPPOINT point = NULL;
        bool ret = GetCursorPos(point);

        // error handling with ret
        return { static_cast<uint32_t>(point->x), static_cast<uint32_t>(point->y) };
    }

    namespace priv
    {
        Mouse::Button mouseButtonConvert(uint64_t _key)
        {
            switch (_key) {
                case MK_LBUTTON: return Mouse::Button::Left;
                case MK_MBUTTON: return Mouse::Button::Middle;
                case MK_RBUTTON: return Mouse::Button::Right;
                case MK_XBUTTON1: return Mouse::Button::X1;
                case MK_XBUTTON2: return Mouse::Button::X2;
                default: return Mouse::Button::Other;
            }
        }
    }
}