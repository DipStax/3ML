#include "M3L/Rendering/Transformable.hpp"

namespace m3l
{
    void Transformable::setPosition(float _x, float _y)
    {
        m_pos.x = _x;
        m_pos.y = _y;
        m_update = true;
    }

    void Transformable::setPosition(const Point2<float> &_pos)
    {
        m_pos = _pos;
        m_update = true;
    }

    void Transformable::move(float _x, float _y)
    {
        m_pos.x += _x;
        m_pos.y += _y;
        m_update = true;
    }

    void Transformable::move(const Point2<float> &_move)
    {
        m_pos += _move;
        m_update = true;
    }

    const Point2<float> &Transformable::getPosition() const
    {
        return m_pos;
    }

    Point2<float> &Transformable::getPosition()
    {
        return m_pos;
    }

    void Transformable::setScale(float _rh, float _rw)
    {
        m_scale.x = _rh;
        m_scale.y = _rw;
        m_update = true;
    }

    void Transformable::setScale(const Point2<float> &_scale)
    {
        m_scale = _scale;
        m_update = true;
    }

    Point2<float> &Transformable::getScale()
    {
        return m_scale;
    }

    const Point2<float> &Transformable::getScale() const
    {
        return m_scale;
    }


    void Transformable::setRotatio(float _rot)
    {
        m_rotation = _rot;
        m_update = true;
    }

    void Transformable::rotate(float _rot)
    {
        m_rotation += _rot;
        m_update = true;
    }

    float Transformable::getRotation() const
    {
        return m_rotation;
    }

    bool Transformable::requiredUpdate() const
    {
        if (!m_update)
            return false;
        m_update = false;
        return true;
    }
}