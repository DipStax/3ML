#pragma once

#include <optional>
#include <tuple>
#include <type_traits>

#include "Tool/Export.hpp"

template<class T>
using UniqueTypeTuple = std::tuple<T>;

namespace imp
{
    template<size_t I, class T, class ...Ts>
    struct tuple_find;

    template<size_t I, class T, class _T, class ...Ts>
    struct tuple_find<I, T, _T, Ts...>
    {
        static constexpr size_t value = std::is_same<T, _T>::value ? I : imp::tuple_find<I, T, Ts...>::value;
    };

    template<size_t I, class T, class _T>
    struct tuple_find<I, T, _T>
    {
        static constexpr size_t value = std::is_same<T, _T>::value ? I : I + 1;
    };

    template<class ...Ts>
    struct tuple_size;

    template<class T, class ...Ts>
    struct tuple_size<T, Ts...>
    {
        static constexpr size_t value = 1 + tuple_size<Ts...>::value;
    };

    template<class T>
    struct tuple_size<T>
    {
        static constexpr size_t value = 1;
    };

    template<class ...Ts>
    struct tuple_prepend;

    template<class T, class ...Ts>
    struct tuple_prepend<T, std::tuple<Ts...>>
    {
        using type = std::tuple<T, Ts...>;
    };

    template<class ...Ts>
    struct tuple_cat;

    template<class ...Ts, class ..._Ts>
    struct tuple_cat<std::tuple<Ts...>, std::tuple<_Ts...>>
    {
        using type = std::tuple<Ts..., _Ts...>;
    };

    template<class ...Ts>
    struct tuple_contain;

    template<class T, class ...Ts>
    struct tuple_contain<T, T, Ts...>
    {
        using type = std::true_type;
    };

    template<class T, class _T, class ...Ts>
    struct tuple_contain<T, _T, Ts...>
    {
        using type = typename imp::tuple_contain<T, Ts...>::type;
    };

    template<class T>
    struct tuple_contain<T>
    {
        using type = std::false_type;
    };

    template<class ...Ts>
    struct unpack_type;

    template<class ...Ts, class ..._Ts>
    struct unpack_type<std::tuple<Ts...>, _Ts...>
    {
        using type = typename tuple_cat<std::tuple<Ts...>, typename imp::unpack_type<_Ts...>::type>::type;
    };

    template<class T, class ...Ts>
    struct unpack_type<T, Ts...>
    {
        using type = typename tuple_prepend<T, typename imp::unpack_type<Ts...>::type>::type;
    };

    template<class T>
    struct unpack_type<T>
    {
        using type = UniqueTypeTuple<T>;
    };

    template<class T, class ...Ts>
    struct unique_type
    {
        using type = std::conditional_t<tuple_contain<T, Ts...>::type::value,
            typename imp::unique_type<Ts...>::type,
            typename tuple_prepend<T, typename imp::unique_type<Ts...>::type>::type>;
    };

    template<class T>
    struct unique_type<T>
    {
        using type = UniqueTypeTuple<T>;
    };

    template<class ...Ts>
    struct is_factory_pair;

    template<class T, class ...Ts>
    struct is_factory_pair<T, Ts...>
    {
        using type = std::false_type;
    };

    template<>
    struct is_factory_pair<>
    {
        using type = std::true_type;
    };

    template<class ...Ts>
    struct pair_key;

    template<class T, class _T, class ...Ts>
    struct pair_key<std::pair<T, _T>, Ts...>
    {
        using type = typename tuple_prepend<T, typename pair_key<Ts...>::type>::type;
    };

    template<>
    struct pair_key<>
    {
        using type = std::tuple<>;
    };

    template<class ...Ts>
    struct tuple_accept_ctr;

    template<class ...Ts>
    class tuple_base_of;

    template<class T, class _T, class __T, class ...Ts>
    struct tuple_base_of<T, std::tuple<std::pair<_T, __T>, Ts...>>
    {
        using type = std::conditional_t<std::is_base_of<T, _T>::value,
            typename tuple_base_of<T, Ts...>::type,
            std::false_type>;
    };
}

template<class T, class ...Ts>
struct tuple_find
{
    static constexpr size_t value = imp::tuple_find<0, T, Ts...>::value;
};

template<class ...Ts>
struct tuple_size
{
    static constexpr size_t value = imp::tuple_size<Ts...>::value;
};

template<class T, class ...Ts>
struct tuple_contain
{
    using type = typename imp::tuple_contain<T, Ts...>::type;
};

template<class ...Ts>
struct tuple_prepend
{
    using type = typename imp::tuple_prepend<Ts...>::type;
};

template<class ...Ts>
struct tuple_cat
{
    using type = typename imp::tuple_cat<Ts...>::type;
};

template<class ...Ts>
struct unpack_type
{
    using type = typename imp::unpack_type<Ts...>::type;
};

template<class ...Ts>
struct unique_type
{
    using type = typename imp::unique_type<Ts...>::type;
};

template<class ...Ts>
struct is_factory_pair
{
    using type = typename imp::is_factory_pair<Ts...>::imp;
};

template<class ...Ts>
struct pair_key
{
    using type = typename imp::pair_key<Ts...>::type;
};

template<class ...Ts>
struct tuple_accept_ctr
{
    using type = typename imp::tuple_accept_ctr<Ts...>::type;
};

template<class ...Ts>
struct tuple_base_of
{
    using type = typename imp::tuple_base_of<Ts...>::type;
};

namespace ecs::sys
{
    class ISystem;
}

namespace m3l::ui
{
    template<class ...Ts>
    class Object;
}

template<class ...Ts>
using Tuple = std::tuple<std::optional<Ts>...>;

namespace opt
{
    template<class T, class ...Ts>
    std::optional<T> &get(Tuple<Ts...> &_tuple) noexcept
    {
        return std::get<std::optional<T>>(_tuple);
    }
}

template<template<typename ...> class T, class _T>
struct is_base_of_template_impl
{
    template<class ...Ts>
    static constexpr std::true_type  test(const T<Ts...> *);
    static constexpr std::false_type test(...);
    using type = decltype(test(std::declval<_T*>()));
};

template<template<typename ...> class base, class derived>
using is_base_of_template = typename is_base_of_template_impl<base, derived>::type;

template<class T, class ...Ts>
concept ContainIn = tuple_contain<T, Ts...>::type::value;

template<class T>
concept SystemType = std::is_base_of<ecs::sys::ISystem, T>::value;

template<class T>
concept NumericType = std::is_arithmetic<T>::value;

template<class T>
concept IsUnsigned = std::unsigned_integral<T>;

template<class T>
concept IsSigned = std::signed_integral<T>;

template<class T>
concept IsFPN = std::floating_point<T>;

template<class T>
concept KeyType = requires (T r, T l)
{
    r < l;
};

template<class T>
concept IsUiObject = is_base_of_template<m3l::ui::Object, T>::type::value;

template<class T>
concept IsString = std::is_same<const char *, T>::value;

template <class T, class... Ts>
concept AcceptCtr = requires (T _l, Ts... _r) {
    T(std::forward<Ts>(_r)...);
};

template<class ...Ts>
concept IsFacPair = is_factory_pair<Ts...>::type::value;

template<class T, class ..._Ts>
concept TupleAcceptCtr = tuple_accept_ctr<typename pair_key<T>::type, _Ts...>::type::value;

template<class T, class ...Ts>
concept IsFacMap = IsFacPair<Ts...> && tuple_base_of<T, typename pair_key<T>::type>::type::value;

template<class T, class _T>
concept IsBasedOf = std::is_base_of_v<T, _T>;

namespace imp
{
    template<IsString T, IsUiObject _T, class ...Ts>
    struct is_factory_pair<std::pair<T, _T>, Ts...>
    {
        using type = imp::is_factory_pair<Ts...>::type;
    };

    template<AcceptCtr T, class ...Ts, class ..._Ts>
    struct tuple_accept_ctr<std::tuple<T, Ts...>, _Ts...>
    {
        using type = typename imp::tuple_accept_ctr<std::tuple<Ts...>, _Ts...>::type;
    };

    template<class T, class ...Ts, class ..._Ts>
    struct tuple_accept_ctr<std::tuple<T, Ts...>, _Ts...>
    {
        using type = std::false_type;
    };

    template<class ..._Ts>
    struct tuple_accept_ctr<std::tuple<>, _Ts...>
    {
        using type = std::true_type;
    };
}

template<class T, class _T>
concept AssignOp = requires (T r, _T l)
{
    r = l;
};

template<class T, class _T>
concept EqOp = requires (T r, _T l)
{
    r == l;
};

template<class T, class _T>
concept NEqOp = requires (T r, _T l)
{
    r != l;
};

template<class T, class _T>
concept LsOp = requires (T r, _T l)
{
    r < l;
};

template<class T, class _T>
concept GtOp = requires (T r, _T l)
{
    r > l;
};

template<class T, class _T>
concept LsEqOp = requires (T r, _T l)
{
    r <= l;
};

template<class T, class _T>
concept GtEqOp = requires (T r, _T l)
{
    r >= l;
};

template<class T, class _T>
concept GlobCompOp = requires (T r, _T l)
{
    r <=> l;
};

template<class T, class _T>
concept AddOp = requires (T r, _T l)
{
    r + l;
};

template<class T, class _T>
concept SubOp = requires (T r, _T l)
{
    r - l;
};

template<class T, class _T>
concept MulOp = requires (T r, _T l)
{
    r * l;
};

template<class T, class _T>
concept DivOp = requires (T r, _T l)
{
    r / l;
};

template<class T, class _T>
concept ModOp = requires (T r, _T l)
{
    r % l;
};

template<class T, class _T>
concept BitAndOp = requires (T r, _T l)
{
    r & l;
};

template<class T, class _T>
concept BitOrOp = requires (T r, _T l)
{
    r | l;
};

template<class T, class _T>
concept BitXorOp = requires (T r, _T l)
{
    r ^ l;
};

template<class T, class _T>
concept LShiftOp = requires (T r, _T l)
{
    r << l;
};

template<class T, class _T>
concept RShiftOp = requires (T r, _T l)
{
    r >> l;
};

template<class T, class _T>
concept AssignAddOp = requires (T r, _T l)
{
    r += l;
};

template<class T, class _T>
concept AssignSubOp = requires (T r, _T l)
{
    r -= l;
};

template<class T, class _T>
concept AssignMulOp = requires (T r, _T l)
{
    r *= l;
};

template<class T, class _T>
concept AssignDivOp = requires (T r, _T l)
{
    r /= l;
};

template<class T, class _T>
concept AssignModOp = requires (T r, _T l)
{
    r %= l;
};

template<class T, class _T>
concept AssignBitAndOp = requires (T r, _T l)
{
    r &= l;
};

template<class T, class _T>
concept AssignBitOrOp = requires (T r, _T l)
{
    r |= l;
};

template<class T, class _T>
concept AssignBitXorOp = requires (T r, _T l)
{
    r ^= l;
};

template<class T, class _T>
concept AssignLShiftOp = requires (T r, _T l)
{
    r <<= l;
};

template<class T, class _T>
concept AssignRShiftOp = requires (T r, _T l)
{
    r >>= l;
};

template<class T>
concept PreIncOp = requires (T r)
{
    r++;
};

template<class T>
concept PostIncOp = requires (T r)
{
    ++r;
};

template<class T>
concept PreDecOp = requires (T r)
{
    r--;
};

template<class T>
concept PostDecOp = requires (T r)
{
    --r;
};