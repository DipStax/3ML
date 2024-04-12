#include <algorithm>

#include "M3L/Rendering/Sprite.hpp"
#include "M3L/Rendering/RenderTarget2D.hpp"

namespace m3l
{
    Sprite::Sprite()
    {
        processRect();
    }

    void Sprite::setTexture(Texture &_img)
    {
        m_txtr = &_img;

        processRect();
    }

    void Sprite::setTxtrRect(Rect _rect)
    {
        m_rect = _rect;
        buildVertex();
    }

    Rect Sprite::getTxtrRect() const
    {
        return m_rect;
    }

    void Sprite::draw(RenderTarget2D &_target, const Texture *_txtr) const
    {
        std::ignore = _txtr;

        buildVertex();
        _target.draw(m_vertex, m_txtr);
    }

    void Sprite::processRect()
    {
        Point2<float> size = (m_txtr) ? m_txtr->getSize().as<float>() : Point2<float>(0.f , 0.f);

        m_rect = { getPosition(), size * getScale() };
        buildVertex(true);
    }

    void Sprite::buildVertex(bool _update) const
    {
        // known bug:
        // - when inversing the pos of the addition for vertex 2 and 4
        // - when inversing m_rect.size for vertex 2 and 4
        if (_update || requiredUpdate())
        {
            m_vertex.clear();
            m_vertex.append({ m_rect.pos, { 0, 0 } });
            m_vertex.append({ { m_rect.pos.x + m_rect.size.x, m_rect.pos.y }, { std::max(m_rect.size.x - 1, 0.f), 0 } });
            m_vertex.append({ m_rect.pos + m_rect.size, { std::max(m_rect.size.x - 1, 0.f), std::max(m_rect.size.y - 1, 0.f) } });
            m_vertex.append({ { m_rect.pos.x, m_rect.pos.y + m_rect.size.y }, { 0, std::max(m_rect.size.y - 1, 0.f) } });
        }
    }
}