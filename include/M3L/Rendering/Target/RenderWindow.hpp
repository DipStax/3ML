#pragma once

#include "M3L/Event/Event.hpp"
#include "M3L/Event/EventPool.hpp"
#include "M3L/Rendering/Target/BaseRenderWindow.hpp"

namespace m3l
{
    using EPWindow = EventPool<Event::Focus, Event::MouseButton, Event::MouseMove, Event::Keyboard, Event::Resize>;

    namespace imp
    {
        template<bool>
        class EnableSysEvent;

        template<>
        class M3L_API EnableSysEvent<true> : public EPWindow
        {
            public:
                explicit EnableSysEvent(ThreadPool &_tp);
                virtual ~EnableSysEvent() = default;
        };

        template<>
        class M3L_API EnableSysEvent<false> {};
    }

    template<bool E = true>
    class RenderWindow : public imp::EnableSysEvent<E>, public BaseRenderWindow
    {
        public:
            RenderWindow(ThreadPool &_tp, uint32_t _x, uint32_t _y, const std::string &_title) requires (E);
            RenderWindow(uint32_t _x, uint32_t _y, const std::string &_title) requires (!E);
            ~RenderWindow() = default;

            bool pollEvent(Event &_event);

        protected:
            void onResize(Event _event) override;
            void onMouseButtonEvent(Event _event) override;
            void onMouseMove(Event _event) override;
            void onKeyboardEvent(Event _event) override;
            void onFocus(Event _event) override;

        private:
            ts::Queue<Event> m_event;
    };
}

#include "M3L/Rendering/Target/RenderWindow.inl"