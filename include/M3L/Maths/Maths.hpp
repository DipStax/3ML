#pragma once

#include "M3L/Maths/Point2.hpp"
#include "M3L/Tool/PreProcessing.hpp"

namespace m3l
{
    template<NumericType T>
    T toRad(T _deg);
    template<NumericType T>
    T toDeg(T _rad);

    template<NumericType T>
    T area(const Vector2<T> &_a, const Vector2<T> &_b, const Vector2<T> &_c);
}

#include "M3L/Maths/Maths.inl"