#pragma once

#include "M3L/Maths/Point2.hpp"

namespace m3l
{
    class M3L_API Transformable
    {
        public:
            Transformable() = default;
            virtual ~Transformable() = default;

            void setPosition(float _x, float _y);
            void setPosition(const Point2<float> &_pos);
            void move(float _x, float _y);
            void move(const Point2<float> &_move);
            [[nodiscard]] const Point2<float> &getPosition() const;
            [[nodiscard]] Point2<float> &getPosition();

            void setScale(float _rh, float _rw);
            void setScale(const Point2<float> &_scale);
            [[nodiscard]] Point2<float> &getScale();
            [[nodiscard]] const Point2<float> &getScale() const;

            void setRotatio(float _rot);
            void rotate(float _rot);
            [[nodiscard]] float getRotation() const;

        protected:
            [[nodiscard]] bool requiredUpdate() const;

        private:
            mutable bool m_update = false;

            Point2<float> m_pos{};
            Point2<float> m_scale = { 1, 1 };
            float m_rotation = 0.f;
    };
}