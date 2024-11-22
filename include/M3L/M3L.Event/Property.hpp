#pragma once

#include <string_view>
#include <tuple>

#include "M3L/Event/EventPool.hpp"
#include "M3L/Tool/PreProcessing.hpp"

namespace m3l
{
    template<class T>
    class Property
    {
        public:
            struct Event
            {
                const std::string name;
                const T &value;
            };

            using PropTrigger = Trigger<Event>;

            template<class ...Ts>
            requires ContainIn<typename Property<T>::Event, Ts...>
            Property(EventPool<Ts...> &_ep, const std::string &_name, T &_val);
            template<class ...Ts, class ..._Ts>
            requires ContainIn<typename Property<T>::Event, Ts...>
            Property(EventPool<Ts...> &_ep, const std::string &_name, _Ts &&..._args);
            Property(Property<T> &&_prop) noexcept;
            Property<T>& operator=(Property<T> &&_prop) noexcept;
            ~Property() = default;

            [[nodiscard]] PropTrigger::sTask subscribe(PropTrigger::Task _task);
            void unsubscribe(PropTrigger::sTask _task);

            void trigger();

            [[nodiscard]] const std::string &getName() const;

            template<AssignOp<T> _T>
            Property<T> &operator=(const _T &_val);
            template<AssignOp<T> _T>
            Property<T> &operator=(const Property<_T> &_val);

            operator T&();
            operator const T&() const;

            // need to return a template value?
            template<EqOp<T> _T>
            [[nodiscard]] bool operator==(const _T &_val) const;
            template<NEqOp<T> _T>
            [[nodiscard]] bool operator!=(const _T &_val) const;
            template<LsOp<T> _T>
            [[nodiscard]] bool operator<(const _T &_val) const;
            template<GtOp<T> _T>
            [[nodiscard]] bool operator>(const _T &_val) const;
            template<LsEqOp<T> _T>
            [[nodiscard]] bool operator<=(const _T &_val) const;
            template<GtEqOp<T> _T>
            [[nodiscard]] bool operator>=(const _T &_val) const;
            template<GlobCompOp<T> _T>
            [[nodiscard]] bool operator<=>(const _T &_val) const;

            template<AddOp<T> _T>
            [[nodiscard]] T operator+(const _T &_val) const;
            template<SubOp<T> _T>
            [[nodiscard]] T operator-(const _T &_val) const;
            template<MulOp<T> _T>
            [[nodiscard]] T operator*(const _T &_val) const;
            template<DivOp<T> _T>
            [[nodiscard]] T operator/(const _T &_val) const;
            template<ModOp<T> _T>
            [[nodiscard]] T operator%(const _T &_val) const;
            template<BitAndOp<T> _T>
            [[nodiscard]] T operator&(const _T &_val) const;
            template<BitOrOp<T> _T>
            [[nodiscard]] T operator|(const _T &_val) const;
            template<BitXorOp<T> _T>
            [[nodiscard]] T operator^(const _T &_val) const;
            template<LShiftOp<T> _T>
            [[nodiscard]] T operator<<(const _T &_val) const;
            template<RShiftOp<T> _T>
            [[nodiscard]] T operator>>(const _T &_val) const;

            template<AssignAddOp<T> _T>
            Property<T> operator+=(const _T &_val);
            template<AssignSubOp<T> _T>
            Property<T> operator-=(const _T &_val);
            template<AssignMulOp<T> _T>
            Property<T> operator*=(const _T &_val);
            template<AssignDivOp<T> _T>
            Property<T> operator/=(const _T &_val);
            template<AssignModOp<T> _T>
            Property<T> operator%=(const _T &_val);
            template<AssignBitAndOp<T> _T>
            Property<T> operator&=(const _T &_val);
            template<AssignBitOrOp<T> _T>
            Property<T> operator|=(const _T &_val);
            template<AssignBitXorOp<T> _T>
            Property<T> operator^=(const _T &_val);
            template<AssignLShiftOp<T> _T>
            Property<T> operator<<=(const _T &_val);
            template<AssignRShiftOp<T> _T>
            Property<T> operator>>=(const _T &_val);

            // requires PreIncOp<T>
            // T operator++();
            // requires PostIncOp<T>
            // Property<T> operator++(int);
            // requires PreDecOp<T>
            // T operator--();
            // requires PostDecOp<T>
            // Property<T> operator--(int);

        private:
            Property(const Property<T> &_prop);
            Property<T> &operator=(const Property<T> &_prop) = delete;

            const std::string m_name;
            Trigger<Property<T>::Event> &m_trigger;

            T m_value;
    };
}

#include "M3L/Event/Property.inl"