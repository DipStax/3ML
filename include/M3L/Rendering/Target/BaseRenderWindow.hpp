#pragma once

#include "M3L/Rendering/Target/RenderTarget2D.hpp"
#include "M3L/Rendering/Target/RenderTarget3D.hpp"
#include "M3L/Core/Window.hpp"

namespace m3l
{
    class M3L_API BaseRenderWindow : public Window, public RenderTarget2D, public RenderTarget3D
    {
        public:
            using RenderTarget2D::draw;
            using RenderTarget3D::draw;

            BaseRenderWindow(uint32_t _x, uint32_t _y, const std::string &_title);
            virtual ~BaseRenderWindow() = default;

            [[nodiscard]] const Point2<uint32_t> &getSize() const;

            void display();

            void clear(const Color &_clr = { 0, 0, 0, 255 });

        protected:
            void create(uint32_t _x, uint32_t _y, const Camera &_cam = Camera(), uint8_t _bpp = 32);

            void render(HDC _draw) const;

        private:
            Point2<uint32_t> m_size;
    };
}