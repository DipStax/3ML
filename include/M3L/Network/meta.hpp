#pragma once

#include "Tool/PreProcessing.hpp"

#define WIN_SOCKET SOCKET

namespace m3l
{
    namespace meta
    {
        namespace imp
        {
            template<template<typename ...> class T, class _T>
            struct is_base_of_template
            {
                template<class ...Ts>
                static constexpr std::true_type  test(const T<Ts...> *);
                static constexpr std::false_type test(...);
                using type = decltype(test(std::declval<_T*>()));
            };
        }

        template<template<typename ...> class T, class _T>
        using is_base_of_template = typename imp::is_base_of_template<T, _T>::type;
    }

    namespace net
    {
        namespace ip
        {
            struct v4;
            struct v6;
        }

        template<class T>
        concept IsBaseIpFormat = IsUInt<typename T::Container> && requires {
                { T::size } -> std::same_as<uint8_t>;
                { T::familly } -> std::same_as<int>;
            } && sizeof(typename T::Container) >= T::size;

        template<class T>
        concept IsBaseIp = (std::same_as<T, m3l::net::ip::v4> || std::same_as<T, m3l::net::ip::v6>);
            //&& IsBaseIpFormat<T>; // template property propagation

        template<class T, class ...Ts>
        concept IsByteIpFormat = IsBaseIpFormat<T> && (sizeof...(Ts) == T::size || (std::is_convertible_v<Ts, uint8_t> && ...));

        template<IsBaseIpFormat T>
        class Ip;

        template<class T>
        concept IsIpFormat = m3l::meta::is_base_of_template<m3l::net::Ip, T>::value;
    }
}