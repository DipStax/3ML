#pragma once

#include "M3L/Rendering/Texture.hpp"

namespace m3l
{
    class RenderTarget2D;

    class IDrawable2D
    {
        protected:
            friend class RenderTarget2D;

            virtual void draw(RenderTarget2D &_target, const Texture *_txtr) const = 0;
    };
}