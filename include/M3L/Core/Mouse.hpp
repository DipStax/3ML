#pragma once

#include <windows.h>

#include "M3L/Maths/Point2.hpp"
#include "M3L/Tool/Export.hpp"

namespace m3l
{
    class M3L_API Mouse
    {
        public:
            enum State {
                Press,
                Neutral,
                Release,
                DoubleClick
            };

            enum Button {
                Right = 0,
                Left = 1,
                Middle = 2,
                X1 = 4,
                X2 = 8,
                Other = 16
            };

            static m3l::Point2<uint32_t> Position();
    };

    namespace priv
    {
        Mouse::Button mouseButtonConvert(uint64_t _key);
    }
}