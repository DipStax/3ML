#pragma once

#include <variant>

namespace extstd
{
    // basic replication of C++ features
    template<class T, class _T>
    class Expected
    {
        public:
            Expected(T _value);
            Expected(_T _error);

            [[nodiscard]] T result();
            [[nodiscard]] _T error();

            [[nodiscard]] constexpr bool has_error() const;

            [[nodiscard]] constexpr operator bool() const;

        private:
            std::variant<T, _T> m_data;

            bool m_error = false;
    };
}

#include "Tool/Expected.inl"