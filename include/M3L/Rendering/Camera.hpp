#pragma once

#include <array>

#include "M3L/Maths/Point3.hpp"
#include "M3L/Maths/Matrix.hpp"

namespace m3l
{
    class M3L_API Camera
    {
        public:
            Camera();
            ~Camera() = default;

            Camera &setFov(float _fov);
            Camera &setRange(float _near, float _far);
            Camera &setSize(float _x, float _y);

            Camera &move(m3l::Vector3<float> _move);
            Camera &rotate(m3l::Vector3<float> _rot);

            [[nodiscard]] m3l::Point3<float> project(m3l::Point3<float> _pt);

            [[nodiscard]] m3l::Point3<float> getPosition() const;

        protected:
            void calculatWorld();
            void calculatProject();

            void perspective(float &_b, float &_t, float &_l, float &_r);
            [[nodiscard]] m3l::Point3<float> transform(m3l::Point3<float> &_pt, const Matrix<4, 4> &_matrix);

        private:
            float m_raspect = 0;
            float m_sizeX = 0;
            float m_sizeY = 0;
            float m_near = 0;
            float m_far = 0;
            float m_fov = 0;
            m3l::Vector3<float> m_rot = { 0, 0, 0 };
            m3l::Vector3<float> m_pos = { 0, 0, 0 };

            Matrix<4, 4> m_mproj;
            Matrix<4, 4> m_mworld;

            Matrix<4, 4> m_mrot;
            Matrix<4, 4> m_mpos;
    };
}