#include <algorithm>
#include <cmath>
#include <numbers>

#include "M3L/Rendering/Camera.hpp"

namespace m3l
{
    Camera::Camera()
    {
        m_mworld.identity();
        m_mrot.identity();
        m_mpos.identity();
        move({ 0, 0, 0 });
        rotate({ 0, 0, 0 });
    }

    Camera &Camera::setFov(float _fov)
    {
        m_fov = _fov;
        calculatProject();
        return *this;
    }

    Camera &Camera::setRange(float _near, float _far)
    {
        m_near = _near;
        m_far = _far;
        calculatProject();
        return *this;
    }

    Camera &Camera::setSize(float _x, float _y)
    {
        m_sizeX = _x;
        m_sizeY = _y;
        m_raspect = m_sizeX / m_sizeY;
        calculatProject();
        return *this;
    }

    Camera &Camera::move(m3l::Vector3<float> _move)
    {
        m_pos += _move;
        m_mpos[3][0] = m_pos.x;
        m_mpos[3][1] = m_pos.y;
        m_mpos[3][2] = m_pos.z;
        calculatWorld();
        return *this;
    }

    Camera &Camera::rotate(m3l::Vector3<float> _rot)
    {
        Matrix<4, 4> rotX;
        Matrix<4, 4> rotY;
        Matrix<4, 4> rotZ;

        m_rot += _rot;
        rotX.identity();
        rotY.identity();
        rotZ.identity();

        rotX[1][1] = std::cos(m_rot.x);
        rotX[1][2] = -std::sin(m_rot.x);
        rotX[2][1] = std::cos(m_rot.x);
        rotX[2][2] = std::sin(m_rot.x);

        rotY[0][0] = std::cos(m_rot.y);
        rotY[0][2] = std::sin(m_rot.y);
        rotY[2][0] = -std::sin(m_rot.y);
        rotY[2][2] = std::cos(m_rot.y);

        rotZ[0][0] = std::cos(m_rot.z);
        rotZ[0][1] = -std::sin(m_rot.z);
        rotZ[1][0] = std::sin(m_rot.z);
        rotZ[1][1] = std::cos(m_rot.z);

        m_mrot = rotZ * rotY * rotX;
        calculatWorld();
        return *this;
    }

    m3l::Point3<float> Camera::project(m3l::Point3<float> _pt)
    {
        m3l::Point3<float> res;
        m3l::Point3<float> cam;
        m3l::Point3<float> proj;

        // http://www.codinglabs.net/article_world_view_projection_matrix.aspx
        cam = transform(_pt, m_mworld);
        proj = transform(cam, m_mproj);
        res.x = std::floor((proj.x + 1.f) * 0.5f * m_sizeX);
        res.y = std::floor((1.f - (proj.y + 1.f) * 0.5f) * m_sizeY);
        res.z = (proj.z + 1) / 2;
        return res;
    }

    Point3<float> Camera::getPosition() const
    {
        return m_pos;
    }

    void Camera::calculatWorld()
    {
        m_mworld = m_mrot * m_mpos;
    }

    void Camera::calculatProject()
    {
        float b;
        float t;
        float r;
        float l;

        perspective(b, t, l, r);
        m_mproj.fill(std::array<float, 4>({ 0, 0, 0, 0 }));
        m_mproj[0][0] = 2 * m_near / (r - l);
        m_mproj[1][1] = 2 * m_near / (t - b);
        m_mproj[0][2] = (r + l) / (r - l);
        m_mproj[1][2] = (t + b) / (t - b);
        m_mproj[2][2] = -(m_far + m_near) / (m_far - m_near);
        m_mproj[3][2] = -1;
        m_mproj[2][3] = -2 * m_far * m_near / (m_far - m_near);
    }

    void Camera::perspective(float &_b, float &_t, float &_l, float &_r)
    {
        float scale = static_cast<float>(tan(m_fov * 0.5 * (std::numbers::pi / 180)) * m_near);

        _r = m_raspect * scale;
        _l = -_r;
        _t = scale;
        _b = -_t;
    }

    m3l::Point3<float> Camera::transform(m3l::Point3<float> &_pt, const Matrix<4, 4> &_matrix)
    {
        m3l::Point3<float> res;
        float w = _pt.x * _matrix[0][3] + _pt.y * _matrix[1][3] + _pt.z * _matrix[2][3] + _matrix[3][3];

        res.x = _pt.x * _matrix[0][0] + _pt.y * _matrix[1][0] + _pt.z * _matrix[2][0] + _matrix[3][0];
        res.y = _pt.x * _matrix[0][1] + _pt.y * _matrix[1][1] + _pt.z * _matrix[2][1] + _matrix[3][1];
        res.z = _pt.x * _matrix[0][2] + _pt.y * _matrix[1][2] + _pt.z * _matrix[2][2] + _matrix[3][2];
        if (w != 1)
            res /= w;
        return res;
    }
}