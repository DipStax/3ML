#include "M3L/Rendering/Target/RenderWindow.hpp"

namespace m3l
{
    namespace imp
    {
        EnableSysEvent<true>::EnableSysEvent(ThreadPool &_tp)
            : EPWindow(_tp)
        {
        }
    }

    template<bool E>
    RenderWindow<E>::RenderWindow(ThreadPool &_tp, uint32_t _x, uint32_t _y, const std::string &_title) requires (E)
        : imp::EnableSysEvent<E>(_tp), BaseRenderWindow(_x, _y, _title)
    {
    }

    template<bool E>
    RenderWindow<E>::RenderWindow(uint32_t _x, uint32_t _y, const std::string &_title) requires (!E)
        : imp::EnableSysEvent<E>(), BaseRenderWindow(_x, _y, _title)
    {
    }

    template<bool E>
    bool RenderWindow<E>::pollEvent(Event &_event)
    {
        disptachEvent();
        if (!m_event.empty())
            _event = m_event.pop_front();
        return !m_event.empty();
    }

    template<bool E>
    void RenderWindow<E>::onResize(Event _event)
    {
        Event::Resize resize = std::get<Event::Resize>( _event.event);

        getCamera().setSize(static_cast<float>(resize.width), static_cast<float>(resize.height));
        create(resize.width, resize.height, getCamera());
        if constexpr (!E)
            this->template raise<Event::Resize>(resize);
        m_event.push(_event);
    }

    template<bool E>
    void RenderWindow<E>::onMouseButtonEvent(Event _event)
    {
        if constexpr (!E)
            this->template raise<Event::MouseButton>(std::get<Event::MouseButton>(_event.event));
        m_event.push(_event);
    }

    template<bool E>
    void RenderWindow<E>::onMouseMove(Event _event)
    {
        if constexpr (E == true)
            this->template raise<Event::MouseMove>(std::get<Event::MouseMove>(_event.event));
        m_event.push(_event);
    }

    template<bool E>
    void RenderWindow<E>::onKeyboardEvent(Event _event)
    {
        if constexpr (E == true)
            this->template raise<Event::Keyboard>(std::get<Event::Keyboard>(_event.event));
        m_event.push(_event);
    }

    template<bool E>
    void RenderWindow<E>::onFocus(Event _event)
    {
        if constexpr (E)
            this->template raise<Event::Focus>(std::get<Event::Focus>(_event.event));
        m_event.push(_event);
    }
}