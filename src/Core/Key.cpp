#include "M3L/Core/Key.hpp"

namespace m3l
{
    Key toKey(uint64_t _key)
    {
        uint64_t key = 0;

        switch (_key) {
            case Key::Enter:
            case Key::Escape:
            case Key::Space:
                return static_cast<Key>(_key);
        }
        if (Key::A <= _key && _key <= Key::Z)
            key = _key;
        else if (Key::NumPad0 <= _key && _key <= Key::NumPad9)
            key = _key;
        else if (Key::F1 <= _key && _key <= Key::F12)
            key = _key;
        else
            return Key::Other;
        return static_cast<Key>(key);
    }

    KeyState getKeyState(Key _key)
    {
        return static_cast<KeyState>(GetKeyState(_key));
    }
}