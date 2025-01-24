#include "M3L/Event/EventPool.hpp"

namespace m3l
{
    template<class ...Ts>
    EventPool<Ts...>::EventPool(ThreadPool& _tp)
        : m_map(_tp)
    {
    }

    template<class ...Ts>
    EventPool<Ts...>::EventPool(EventPool<Ts...> &&_ep) noexcept
        : m_map(std::move(_ep.m_map))
    {
    }

    template<class ...Ts>
    template<class T>
    requires ContainIn<T, Ts...>
    bool EventPool<Ts...>::raise(const T &_event)
    {
        m_map.template at<T>().raise(_event);
        return true;
    }

    template<class ...Ts>
    template<class T>
    requires ContainIn<T, Ts...>
    Trigger<T>::sTask EventPool<Ts...>::subscribe(Trigger<T>::Task _task)
    {
        return m_map.template at<T>().subscribe(_task);
    }

    template<class ...Ts>
    template<class T>
    requires ContainIn<T, Ts...>
    void EventPool<Ts...>::unsubscribe(Trigger<T>::sTask _task)
    {
        m_map.template at<T>().unsubscribe(_task);
    }

    template<class ...Ts>
    template<class T>
    requires ContainIn<T, Ts...>
    Trigger<T> &EventPool<Ts...>::getTrigger()
    {
        return m_map.template at<T>();
    }
}