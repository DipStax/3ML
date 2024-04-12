#pragma once

#include "M3L/Container/TriggerMap.hpp"
#include "M3L/Event/Event.hpp"
#include "M3L/Event/Trigger.hpp"

namespace m3l
{
    // check for tuple inside of ts
    template<class ...Ts>
    class EventPool
    {
        public:
            EventPool(ThreadPool &_tp);
            EventPool(EventPool<Ts...> &&_ep) noexcept;
            virtual ~EventPool() = default;

            template<class T>
            requires ContainIn<T, Ts...>
            bool raise(const T &_event);

            template<class T>
            requires ContainIn<T, Ts...>
            Trigger<T>::sTask subscribe(Trigger<T>::Task _task);
            template<class T>
            requires ContainIn<T, Ts...>
            void unsubscribe(Trigger<T>::sTask _task);

            template<class T>
            requires ContainIn<T, Ts...>
            Trigger<T> &getTrigger();

        private:
            TriggerMap<Trigger, std::tuple<Ts...>> m_map;
            // return the trigger from the pool event to the property
    };
}

#include "M3L/Event/EventPool.inl"