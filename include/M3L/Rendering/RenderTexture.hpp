#pragma once

#include "M3L/Rendering/RenderTarget2D.hpp"
#include "M3L/Rendering/RenderTarget3D.hpp"

template<class T>
concept IsRenderTarget = requires (T _t, uint32_t _p32, uint8_t _p8) {
    { _t.getData() } -> std::same_as<const uint8_t *>;
    { _t.create(_p32, _p32, _p8) } -> std::same_as<void>;
};

namespace m3l
{
    template<IsRenderTarget T>
    class M3L_API RenderTexture : public T
    {
        public:
            RenderTexture() = default;
            ~RenderTexture() = default;

            void create(uint32_t _x, uint32_t _y, uint8_t _bpp = 32);

            [[nodiscard]] Texture getTexture() const;
            [[nodiscard]] Point2<uint32_t> getSize() const;

        private:
            Point2<uint32_t> m_size;
    };

    using RenderTexture2D = RenderTexture<RenderTarget2D>;
    using RenderTexture3D = RenderTexture<RenderTarget3D>;
}

#include "M3L/Rendering/RenderTexture.hpp"