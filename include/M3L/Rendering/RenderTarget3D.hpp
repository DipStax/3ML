#pragma once

#include "M3L/Rendering/IDrawable3D.hpp"
#include "M3L/Rendering/VertexArray.hpp"
#include "M3L/Rendering/Camera.hpp"

namespace m3l
{
    class M3L_API RenderTarget3D
    {
        public:
            virtual ~RenderTarget3D();

            void setCamera(const Camera &_cam);
            [[nodiscard]] const Camera &getCamera() const;
            [[nodiscard]] Camera &getCamera();

            void setBpp(uint8_t _bpp);
            [[nodiscard]] uint8_t getBpp() const;

            [[nodiscard]] virtual const Point2<uint32_t> &getSize() const = 0;

            void draw(const IDrawable3D &_elem, const Texture *_txtr = nullptr);
            void draw(const Vertex3D *_vtx, size_t _size, const Texture *_txtr);

        protected:
            RenderTarget3D() = default;

            void create(uint32_t _x, uint32_t _y, uint8_t _bpp = 32);
            void create(uint32_t _x, uint32_t _y, const Camera& _cam, uint8_t _bpp = 32);

            void clear(const Color &_clr = { 0, 0, 0, 255 });

            [[nodiscard]] const uint8_t *getData() const;

        private:
            void drawTriangle(const Vertex3D *_vtx, int32_t _line, const Point2<uint32_t> &_range, const Texture * _txtr);

            void setPixel(const Point2<uint32_t> &_pos, Color _clr, float _depth);

            Camera m_cam;
            HBITMAP m_dib;
            std::vector<float> m_depth;
            uint8_t *m_data = nullptr;
            uint8_t m_bpp;
    };
}