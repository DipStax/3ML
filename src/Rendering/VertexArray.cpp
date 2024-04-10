#include "M3L/Rendering/RenderTarget2D.hpp"
#include "M3L/Rendering/VertexArray.hpp"

namespace m3l
{
    VertexArray::VertexArray(size_t _n)
        : m_pos(_n)
    {
    }

    void VertexArray::setType(Type _type)
    {
        m_type = _type;
    }

    VertexArray::Type VertexArray::getType() const
    {
        return m_type;
    }

    void VertexArray::resize(size_t _n)
    {
        m_pos.resize(_n);
    }

    void VertexArray::append(const Vertex2D &_px)
    {
        m_pos.emplace_back(_px);
    }

    size_t VertexArray::size() const
    {
        return m_pos.size();
    }

    Vertex2D &VertexArray::operator[](size_t _idx)
    {
        return m_pos[_idx];
    }

    Vertex2D *VertexArray::data()
    {
        return m_pos.data();
    }

    const Vertex2D *VertexArray::data() const
    {
        return m_pos.data();
    }

    void VertexArray::clear()
    {
        m_pos.clear();
    }

    void VertexArray::draw(RenderTarget2D &_target, const Texture *_txtr) const
    {
        if (!m_pos.empty()) {
            if (_txtr)
                _target.draw(m_pos.data(), m_pos.size(), _txtr);
            else
                _target.draw(m_pos.data(), m_pos.size(), m_type);
        }
    }
}