#include <map>

#include <Windows.h>
#include <windowsx.h>

#include "M3L/Core/Key.hpp"
#include "M3L/Core/Window.hpp"

namespace Win
{
    HWND find(LPCTSTR _name, LPCTSTR _class)
    {
        return FindWindow(_class, _name);
    }
}

namespace m3l
{
    Window::Window(uint32_t _x, uint32_t _y, const std::string& _title)
    {
        open(_x, _y, _title);
    }

    Window::~Window()
    {
        close();
    }

    void Window::open(uint32_t _x, uint32_t _y, const std::string& _title)
    {
        if (m_open)
            close();
        m_winClass = {
                .style = CS_VREDRAW | CS_DBLCLKS,
                .lpfnWndProc = WIN_proc,
                .cbClsExtra = 0,
                .cbWndExtra = 0,
                .hInstance = GetModuleHandle(NULL),
                .hIcon = NULL,
                .hCursor = NULL,
                .hbrBackground = (HBRUSH)(COLOR_WINDOW + 1),
                .lpszMenuName = NULL,
                .lpszClassName = WIN_className,
        };
        RegisterClass(&m_winClass);
        m_win = CreateWindowEx(0, WIN_className, _title.c_str(), WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            CW_USEDEFAULT, CW_USEDEFAULT, _x, _y, NULL, NULL, m_winClass.hInstance, this
        );
        m_dc = getDc();
        m_open = true;
    }

    bool Window::isOpen() const
    {
        return m_open;
    }

    void Window::setTitle(const std::string& _title)
    {
        bool ret = SetWindowText(m_win, _title.c_str());

        // error handling with ret
    }

    std::string Window::getTitle() const
    {
        std::string title(WIN_MAXTITLE, '\0');
        int ret = GetWindowText(m_win, const_cast<char*>(title.c_str()), WIN_MAXTITLE);

        // error handling with ret
        return title;
    }

    void Window::move(uint32_t _x, int32_t _y)
    {
        Point2<uint32_t> pos = getPosition();

       setPosition(pos.x + _x, pos.y + _y);
    }

    void Window::setPosition(uint32_t _x, uint32_t _y)
    {
        Point2<uint32_t> size = Window::getSize();
        bool ret = move(size.x, size.y, _x, _y);

        // error handling with ret
    }

    Point2<uint32_t> Window::getPosition() const
    {
        RECT rect;
        bool ret = winRect(&rect);

        // error handling with ret
        return Point2<uint32_t>{ static_cast<uint32_t>(rect.left), static_cast<uint32_t>(rect.top) };
    }

    void Window::setSize(uint32_t _x, uint32_t _y)
    {
        Point2<uint32_t> pos = Window::getPosition();
        bool ret = move(_x, _y, pos.x, pos.y);

        // error handling with ret
    }

    Point2<uint32_t> Window::getSize() const
    {
        RECT rect;
        bool ret = winRect(&rect);

        // error handling with ret
        return Point2<uint32_t>{ static_cast<uint32_t>(rect.right - rect.left), static_cast<uint32_t>(rect.bottom - rect.top) };
    }

    void Window::disptachEvent()
    {
        MSG msg;

        while (PeekMessage(&msg, m_win, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    void Window::close()
    {
        ReleaseDC(m_win, m_dc);
        DestroyWindow(m_win);
        m_open = false;
    }

    HWND Window::getWindow() const
    {
        return m_win;
    }

    void Window::onResize(Event _event)
    {
        std::ignore = _event;
    }

    void Window::onMouseButtonEvent(Event _event)
    {
        std::ignore = _event;
    }

    void Window::onMouseMove(Event _event)
    {
        std::ignore = _event;
    }

    void Window::onKeyboardEvent(Event _event)
    {
        std::ignore = _event;
    }

    void Window::onFocus(Event _event)
    {
        std::ignore = _event;
    }

    void Window::resized(uint64_t _wparam, uint64_t _lparam)
    {
        Event ev{};

        if (_wparam == SIZE_MAXHIDE || _wparam == SIZE_MAXSHOW)
            return;
        ev.type = Event::Type::Resize;
        ev.event = Event::Resize{
            HIWORD(_lparam),
            LOWORD(_lparam)
        };
        onResize(ev);
    }

    void Window::mouseButtonEvent(Mouse::State _state, uint64_t _wparam)
    {
        Event ev{};

        if (_wparam == MK_CONTROL || _wparam == MK_SHIFT)
            return;
        ev.type = Event::Type::MouseButton;
        ev.event = Event::MouseButton{
            _state,
            priv::mouseButtonConvert(_wparam)
        };
        onMouseButtonEvent(ev);
    }

    void Window::mouseMove(uint64_t _lparam)
    {
        Event ev{};

        ev.type = Event::Type::MouseMove;
        ev.event = Event::MouseMove{
            GET_X_LPARAM(_lparam),
            GET_Y_LPARAM(_lparam)
        };
        onMouseMove(ev);
    }

    void Window::keyboardEvent(KeyState _state, uint64_t _wparam)
    {
        Event ev{};

        ev.type = Event::Type::KeyBoard;
        ev.event = Event::Keyboard{ toKey(_wparam),
            _state,
            getKeyState(Key::Control),
            getKeyState(Key::Alt),
            getKeyState(Key::Shift)
        };
        onKeyboardEvent(ev);
    }

    void Window::focus(bool _state)
    {
        Event ev{};

        ev.type = Event::Type::Focus;
        ev.event = Event::Focus{ _state };
        onFocus(ev);
    }

    LRESULT CALLBACK Window::WIN_proc(HWND _win, UINT _msg, WPARAM _wparam, LPARAM _lparam)
    {
        PAINTSTRUCT ps;
        Window *pthis;

        if (_msg == WM_NCCREATE) {
            CREATESTRUCT* create = (CREATESTRUCT*)_lparam;

            pthis = (Window *)create->lpCreateParams;
            SetWindowLongPtr(_win, GWLP_USERDATA, (LONG_PTR)pthis);
            //pthis->enableMouseTracking();
        } else {
            pthis = (Window *)GetWindowLongPtr(_win, GWLP_USERDATA);
        }
        if (pthis->messageKeyBoard(_msg, _wparam, _lparam))
            return 0;
        switch (_msg) {
            case WM_PAINT: {
                    HDC hdc = BeginPaint(_win, &ps);
                    pthis->render(hdc);
                    EndPaint(_win, &ps);
                    ReleaseDC(pthis->getWindow(), hdc);
                }
                break;
            case WM_SIZE:
                pthis->resized(_wparam, _lparam);
                break;
            case WM_RBUTTONDOWN:
            case WM_MBUTTONDOWN:
            case WM_LBUTTONDOWN:
            case WM_XBUTTONDOWN:
                pthis->mouseButtonEvent(Mouse::State::Press, _wparam);
                break;
            case WM_RBUTTONUP:
            case WM_MBUTTONUP:
            case WM_LBUTTONUP:
            case WM_XBUTTONUP:
                pthis->mouseButtonEvent(Mouse::State::Release, _wparam);
                break;
            case WM_RBUTTONDBLCLK:
            case WM_LBUTTONDBLCLK:
            case WM_MBUTTONDBLCLK:
            case WM_XBUTTONDBLCLK:
                pthis->mouseButtonEvent(Mouse::State::DoubleClick, _wparam);
                break;
            case WM_MOUSEMOVE:
                pthis->mouseMove(_lparam);
                break;
            case WM_KILLFOCUS:
                pthis->focus(false);
                break;
            case WM_SETFOCUS:
                pthis->focus(true);
                break;
            case WM_DESTROY:
                PostQuitMessage(0);
                pthis->close();
                break;
            default:
                return DefWindowProc(_win, _msg, _wparam, _lparam);
        }
        return 0;
    }

    bool Window::messageKeyBoard(UINT _msg, WPARAM _wparam, LPARAM _lparam)
    {
        std::ignore = _lparam;

        switch (_msg) {
            case WM_KEYDOWN:
                keyboardEvent(KeyState::Down, _wparam);
                break;
            case WM_KEYUP:
                keyboardEvent(KeyState::Up, _wparam);
                break;
            default:
                return false;
        }
        return true;
    }

    HDC Window::getDc() const
    {
        return m_dc;
    }

    bool Window::peekMessage(LPMSG _msg) const
    {
        return PeekMessage(_msg, m_win, 0, 0, PM_REMOVE);
    }

    bool Window::winRect(LPRECT _rect) const
    {
        return GetWindowRect(m_win, _rect);
    }

    bool Window::move(uint32_t _x, uint32_t _y, uint32_t _width, uint32_t _height) const
    {
        return MoveWindow(m_win, _x, _y, _width, _height, true);
    }
}