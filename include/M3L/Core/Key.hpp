#pragma once

#include <cstdint>

#include <windows.h>

namespace m3l
{
    enum KeyState
    {
        Up,
        Down
    };

    enum Key
    {
        Other,
        Enter = VK_RETURN,
        Alt = VK_MENU,
        Escape = VK_ESCAPE,
        Space = VK_SPACE,
        Key0 = 0x30,
        Key1,
        Key2,
        Key3,
        Key4,
        Key5,
        Key6,
        Key7,
        Key8,
        Key9,
        A = 0x41,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        NumPad0 = VK_NUMPAD0,
        NumPad1,
        NumPad2,
        NumPad3,
        NumPad4,
        NumPad5,
        NumPad6,
        NumPad7,
        NumPad8,
        NumPad9,
        F1 = VK_F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        Shift = VK_SHIFT,
        Control = VK_CONTROL,
    };

    Key toKey(uint64_t _key);
    KeyState getKeyState(Key _key);
}