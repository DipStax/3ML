#pragma once

#include "M3L/Rendering/VertexArray.hpp"
#include "M3L/Rendering/Rect.hpp"
#include "M3L/Rendering/IDrawable2D.hpp"
#include "M3L/Rendering/Texture.hpp"
#include "M3L/Rendering/Transformable.hpp"

namespace m3l
{
    class M3L_API Sprite : public Transformable, public IDrawable2D
    {
        public:
            Sprite();
            ~Sprite() = default;

            void setTexture(Texture &_img);

            void setTxtrRect(Rect _rect);
            [[nodiscard]] Rect getTxtrRect() const;

        protected:
            void draw(RenderTarget2D &_target, const Texture *_txtr) const override;

        private:
            void processRect();
            void buildVertex(bool _update = false) const;

            Texture *m_txtr = nullptr;

            mutable VertexArray m_vertex{};

            Rect m_rect;
    };
}