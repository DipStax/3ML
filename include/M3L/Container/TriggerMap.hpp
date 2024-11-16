#pragma once

#include <type_traits>
#include <tuple>
#include <map>
#include <cstddef>

#include "M3L/Core/ThreadPool.hpp"
#include "M3L/Tool/PreProcessing.hpp"

namespace m3l
{
    template<template<class> class T, class ...Ts>
    class TriggerMap;

    template<template<class> class T, class ...Ts>
    class TriggerMap<T, std::tuple<Ts...>>
    {
        public:
            TriggerMap(ThreadPool &_tp);
            TriggerMap(TriggerMap<T, std::tuple<Ts...>> &&_tm) noexcept;
            ~TriggerMap() = default;

            template<class _T>
            requires ContainIn<_T, Ts...>
            constexpr size_t find() const noexcept;

            template<class _T>
            requires ContainIn<_T, Ts...>
            [[nodiscard]] constexpr const T<_T> &at() const noexcept;
            template<class _T>
            requires ContainIn<_T, Ts...>
            [[nodiscard]] constexpr T<_T> &at() noexcept;

        private:
            std::tuple<T<Ts>...> m_tup;
    };
}
#include "M3L/Container/TriggerMap.inl"