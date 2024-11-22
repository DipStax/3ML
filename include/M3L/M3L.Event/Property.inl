#include "M3L/Event/Property.hpp"

namespace m3l
{
    template<class T>
    template<class ...Ts>
    requires ContainIn<typename Property<T>::Event, Ts...>
    Property<T>::Property(EventPool<Ts...> &_ep, const std::string &_name, T &_value)
        : m_name(_name), m_trigger(_ep.template getTrigger<T>())/*m_ep(_ep)*/, m_value(_value)
    {
    }

    template<class T>
    template<class ...Ts, class ..._Ts>
    requires ContainIn<typename Property<T>::Event, Ts...>
    Property<T>::Property(EventPool<Ts...> &_ep, const std::string &_name, _Ts &&..._args)
        : m_name(_name), m_trigger(_ep.template getTrigger<Property<T>::Event>()), m_value(std::forward<_Ts>(_args)...)
    {
    }

    template<class T>
    Property<T>::Property(Property<T> &&_prop) noexcept
        : m_name(std::move(_prop.m_name)), m_trigger(_prop.m_trigger), m_value(std::move(_prop.m_value))
    {
    }

    template<class T>
    Property<T> &Property<T>::operator=(Property<T> &&_prop) noexcept
    {
        if (this != &_prop) {
            m_name = std::move(_prop.m_name);
            m_trigger = _prop.m_trigger;
            m_value = std::move(_prop.m_value);
            _prop.m_trigger = nullptr;
        }
        return *this;
    }

    template<class T>
    Property<T>::PropTrigger::sTask Property<T>::subscribe(PropTrigger::Task _task)
    {
        return m_trigger.subscribe(_task);
    }

    template<class T>
    void Property<T>::unsubscribe(PropTrigger::sTask _task)
    {
        m_trigger.unsubscribe(_task);
    }

    template<class T>
    void Property<T>::trigger()
    {
        m_trigger.raise({ m_name, m_value });
    }

    template<class T>
    const std::string &Property<T>::getName() const
    {
        return m_name;
    }

#pragma region Property operator

    template<class T>
    template<AssignOp<T> _T>
    Property<T> &Property<T>::operator=(const _T &_val)
    {
        m_value = _val;
        trigger();
        return *this;
    }

    template<class T>
    template<AssignOp<T> _T>
    Property<T> &Property<T>::operator=(const Property<_T> &_val)
    {
        m_value = _val.m_value;
        trigger();
        return *this;
    }

    template<class T>
    Property<T>::operator T&()
    {
        return m_value;
    }

    template<class T>
    Property<T>::operator const T&() const
    {
        return m_value;
    }

    template<class T>
    template<EqOp<T> _T>
    bool Property<T>::operator==(const _T &_val) const
    {
        return m_value == _val;
    }

    template<class T>
    template<NEqOp<T> _T>
    bool Property<T>::operator!=(const _T &_val) const
    {
        return m_value != _val;
    }

    template<class T>
    template<LsOp<T> _T>
    bool Property<T>::operator<(const _T &_val) const
    {
        return m_value < _val;
    }

    template<class T>
    template<GtOp<T> _T>
    bool Property<T>::operator>(const _T &_val) const
    {
        return m_value > _val;
    }

    template<class T>
    template<LsEqOp<T> _T>
    bool Property<T>::operator<=(const _T &_val) const
    {
        return m_value <= _val;
    }

    template<class T>
    template<GtEqOp<T> _T>
    bool Property<T>::operator>=(const _T &_val) const
    {
        return m_value >= _val;
    }

    template<class T>
    template<GlobCompOp<T> _T>
    bool Property<T>::operator<=>(const _T &_val) const
    {
        return m_value <=> _val;
    }

    template<class T>
    template<AddOp<T> _T>
    T Property<T>::operator+(const _T &_val) const
    {
        return m_value + _val;
    }

    template<class T>
    template<SubOp<T> _T>
    T Property<T>::operator-(const _T &_val) const
    {
        return m_value - _val;
    }

    template<class T>
    template<MulOp<T> _T>
    T Property<T>::operator*(const _T &_val) const
    {
        return m_value * _val;
    }

    template<class T>
    template<DivOp<T> _T>
    T Property<T>::operator/(const _T &_val) const
    {
        return m_value / _val;
    }

    template<class T>
    template<ModOp<T> _T>
    T Property<T>::operator%(const _T &_val) const
    {
        return m_value % _val;
    }

    template<class T>
    template<BitAndOp<T> _T>
    T Property<T>::operator&(const _T &_val) const
    {
        return m_value & _val;
    }

    template<class T>
    template<BitOrOp<T> _T>
    T Property<T>::operator|(const _T &_val) const
    {
        return m_value | _val;
    }

    template<class T>
    template<BitXorOp<T> _T>
    T Property<T>::operator^(const _T &_val) const
    {
        return m_value ^ _val;
    }

    template<class T>
    template<LShiftOp<T> _T>
    T Property<T>::operator<<(const _T &_val) const
    {
        return m_value << _val;
    }

    template<class T>
    template<RShiftOp<T> _T>
    T Property<T>::operator>>(const _T &_val) const
    {
        return m_value >> _val;
    }

    template<class T>
    template<AssignAddOp<T> _T>
    Property<T> Property<T>::operator+=(const _T &_val)
    {
        m_value += _val;
        trigger();
        return *this;
    }

    template<class T>
    template<AssignSubOp<T> _T>
    Property<T> Property<T>::operator-=(const _T &_val)
    {
        m_value -= _val;
        trigger();
        return *this;
    }

    template<class T>
    template<AssignMulOp<T> _T>
    Property<T> Property<T>::operator*=(const _T &_val)
    {
        m_value *= _val;
        trigger();
        return *this;
    }

    template<class T>
    template<AssignDivOp<T> _T>
    Property<T> Property<T>::operator/=(const _T &_val)
    {
        m_value /= _val;
        trigger();
        return *this;
    }

    template<class T>
    template<AssignModOp<T> _T>
    Property<T> Property<T>::operator%=(const _T &_val)
    {
        m_value %= _val;
        trigger();
        return *this;
    }

    template<class T>
    template<AssignBitAndOp<T> _T>
    Property<T> Property<T>::operator&=(const _T &_val)
    {
        m_value &= _val;
        trigger();
        return *this;
    }

    template<class T>
    template<AssignBitOrOp<T> _T>
    Property<T> Property<T>::operator|=(const _T &_val)
    {
        m_value |= _val;
        trigger();
        return *this;
    }

    template<class T>
    template<AssignBitXorOp<T> _T>
    Property<T> Property<T>::operator^=(const _T &_val)
    {
        m_value ^= _val;
        trigger();
        return *this;
    }

    template<class T>
    template<AssignLShiftOp<T> _T>
    Property<T> Property<T>::operator<<=(const _T &_val)
    {
        m_value <<= _val;
        trigger();
        return *this;
    }

    template<class T>
    template<AssignRShiftOp<T> _T>
    Property<T> Property<T>::operator>>=(const _T &_val)
    {
        m_value >>= _val;
        trigger();
        return *this;
    }

    // template<class T>
    // requires PreIncOp<T>
    // Property<T> Property<T>::operator++()
    // {
    //     m_value++;
    //     return *this;
    // }

    // template<class T>
    // requires PostIncOp<T>
    // Property<T> Property<T>::operator++(int)
    // {
    //     ++m_value;
    //     return *this;
    // }

    // template<class T>
    // requires PreDecOp<T>
    // Property<T> Property<T>::operator--()
    // {
    //     m_value--;
    //     return *this;
    // }

    // template<class T>
    // requires PostDecOp<T>
    // Property<T> Property<T>::operator--(int)
    // {
    //     --m_value;
    //     return *this;
    // }

#pragma endregion
}