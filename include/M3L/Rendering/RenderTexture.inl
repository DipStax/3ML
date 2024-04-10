#include "M3L/Rendering/RenderTexture.hpp"

namespace m3l
{
    template<IsRenderTarget T>
    void RenderTexture<T>::create(uint32_t _x, uint32_t _y, uint8_t _bpp)
    {
        m_size = { _x, _y };
        T::create(_x, _y, _bpp);
    }

    template<IsRenderTarget T>
    Texture RenderTexture<T>::getTexture() const
    {
        Texture txtr;

        txtr.load(getData(), m_size);
        return txtr;
    }

    template<IsRenderTarget T>
    Point2<uint32_t> RenderTexture<T>::getSize() const
    {
        return m_size;
    }
}