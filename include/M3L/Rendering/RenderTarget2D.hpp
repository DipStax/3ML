#pragma once

#include "M3L/Rendering/IDrawable2D.hpp"
#include "M3L/Rendering/VertexArray.hpp"

namespace m3l
{
    class M3L_API RenderTarget2D
    {
        public:
            virtual ~RenderTarget2D();

            void setBpp(uint8_t _bpp);
            [[nodiscard]] uint8_t getBpp() const;

            [[nodiscard]] virtual const Point2<uint32_t> &getSize() const = 0;

            void draw(const IDrawable2D &_elem, const Texture *_txtr = nullptr);
            void draw(const Vertex2D *_vtx, size_t _size, const Texture *_txtr);
            void draw(const Vertex2D *_vtx, size_t _size, VertexArray::Type _type);

        protected:
            RenderTarget2D() = default;

            void create(uint32_t _x, uint32_t _y, uint8_t _bpp = 32);

            void clear(const Color &_clr = { 0, 0, 0, 255 });

            [[nodiscard]] const uint8_t *getData() const;

        private:
            void drawLine(const Vertex2D &_start, const Vertex2D &_end);

            void drawTriangle(const Vertex2D *_vtx, int32_t _line, const Point2<uint32_t> &_range, const Texture *_txtr);
            void drawTriangle(const Vertex2D *_vtx, int32_t _line, const Point2<uint32_t>& _range);

            void setPixel(const Point2<uint32_t> &_pos, Color _clr);

            HBITMAP m_dib = nullptr;
            uint8_t *m_data = nullptr;
            uint8_t m_bpp;
    };
}