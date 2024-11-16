#pragma once

#include <functional>
#include <memory>
#include <vector>

#include "M3L/Event/Event.hpp"
#include "M3L/Core/ThreadPool.hpp"

namespace m3l
{
    template<class T>
    class Trigger
    {
        public:
            using Task = std::function<void(const T&)>;
            using sTask = std::shared_ptr<std::function<void(const T&)>>;

            Trigger(ThreadPool &_tp);
            ~Trigger() = default;

            void raise(const T &_event);
            void raise(const T &_event, const sTask _not);

            [[nodiscard]] sTask subscribe(Task _task);
            void unsubscribe(const sTask _task);

        private:
            std::vector<sTask> m_sub;

            ThreadPool &m_tp;
    };
}

#include "M3L/Event/Trigger.inl"