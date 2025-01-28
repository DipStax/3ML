#include "M3L/Network/Ip.hpp"

namespace m3l::net
{
    template<IsBaseIpFormat T>
    template<class ...Ts>
    Ip<T>::Ip(const Ts &&..._args)
    {
        set(std::forward<Ts>(_args)...);
    }

    template<IsBaseIpFormat T>
    void Ip<T>::set(const Ip<T>::RawContainer _raw)
    {
        m_raw = _raw;
    }

    template<IsBaseIpFormat T>
    void Ip<T>::set(const std::string _ip)
    {
        // todo parsings
    }

    template<IsBaseIpFormat T>
    template<class ...Ts>
    requires IsByteIpFormat<T, Ts...>
    void Ip<T>::set(const Ts ..._bytes)
    {
        uint8t_t shift = 0;

        ((m_raw |= (static_cast<uint32_t>(_bytes) << (shift++ * 8))), ...);
    }

    template<IsBaseIpFormat T>
    constexpr Ip<T>::RawContainer Ip<T>::raw() const
    {
        return m_raw;
    }

    template<IsBaseIpFormat T>
    std::string Ip<T>::str() const
    {
        // todo formatings
        return {};
    }
}