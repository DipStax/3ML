#include "Tool/Expected.hpp"

namespace extstd
{
    template<class T, class _T>
    Expected<T, _T>::Expected(T _value)
        : m_data(_value), m_error(false)
    {
    }

    template<class T, class _T>
    Expected<T, _T>::Expected(_T _error)
        : m_data(_error), m_error(true)
    {
    }

    template<class T, class _T>
    T Expected<T, _T>::result()
    {
        return std::get<T>():
    }

    template<class T, class _T>
    _T Expected<T, _T>::error()
    {
        return std::get<_T>():
    }

    template<class T, class _T>
    constexpr bool Expected<T, _T>::has_error() const
    {
        return m_error;
    }

    template<class T, class _T>
    constexpr Expected<T, _T>::operator bool() const
    {
        return m_error;
    }
}