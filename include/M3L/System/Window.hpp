#pragma once

#include <string>
#include <thread>

#include <windows.h>

#include "M3L/Maths/Point2.hpp"
#include "M3L/Rendering/Color.hpp"
#include "M3L/Event/Event.hpp"

#ifndef WIN_MAXTITLE
    #define WIN_MAXTITLE 256
#endif

namespace m3l
{
    class M3L_API Window
    {
        public:
            Window(uint32_t _x, uint32_t _y, const std::string& _title);
            virtual ~Window();

            void open(uint32_t _x, uint32_t _y, const std::string& _title);
            [[nodiscard]] bool isOpen() const;

            void setTitle(const std::string& _title);
            [[nodiscard]] std::string getTitle() const;

            void move(uint32_t _x, int32_t _y);
            void setPosition(uint32_t _x, uint32_t _y);
            [[nodiscard]] Point2<uint32_t> getPosition() const;

            void setSize(uint32_t _x, uint32_t _y);
            [[nodiscard]] Point2<uint32_t> getSize() const;

            void close();

        protected:
            void disptachEvent();

            [[nodiscard]] HWND getWindow() const;

            virtual void onResize(Event _event);
            virtual void onMouseButtonEvent(Event _event);
            virtual void onMouseMove(Event _event);
            virtual void onKeyboardEvent(Event _event);
            virtual void onFocus(Event _event);

        private:
            void resized(uint64_t _wparam, uint64_t _lparam);
            void mouseButtonEvent(Mouse::State _state, uint64_t _wparam);
            void mouseMove(uint64_t _wparam);
            void keyboardEvent(KeyState _state, uint64_t _wparam);
            void focus(bool _state);

            static LRESULT CALLBACK WIN_proc(HWND _win, UINT _msg, WPARAM _wparam, LPARAM _lparam);

            bool messageKeyBoard(UINT _msg, WPARAM _wparam, LPARAM _lparam);

            static constexpr char WIN_className[] = "Sample Window Class";

            [[nodiscard]] HDC getDc() const;

            bool peekMessage(LPMSG _msg) const;
            bool winRect(LPRECT _rect) const;
            bool move(uint32_t _x, uint32_t _y, uint32_t _width, uint32_t _height) const;

            virtual void render(HDC _draw) const = 0;

            WNDCLASS m_winClass{};
            HWND m_win;
            HDC m_dc;
            bool m_open = false;
    };
}