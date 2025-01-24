#pragma once

#include "M3L/Rendering/Texture.hpp"

namespace m3l
{
    class RenderTarget3D;

    class IDrawable3D
    {
        protected:
            friend class RenderTarget3D;

            virtual void draw(RenderTarget3D &_target, const Texture *_txtr) const = 0;
    };
}