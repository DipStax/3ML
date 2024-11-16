#pragma once

#include <variant>

#include "M3L/Core/Mouse.hpp"
#include "M3L/Core/Key.hpp"

namespace m3l
{
    struct M3L_API Event
    {
        struct Focus
        {
            bool state = false;
        };

        struct MouseButton
        {
            Mouse::State state = Mouse::State::Neutral;
            Mouse::Button button = Mouse::Button::Other;
        };

        struct MouseMove
        {
            int32_t x = 0;
            int32_t y = 0;
        };

        struct Keyboard
        {
            Key key = Key::Other;
            KeyState state = KeyState::Down;
            KeyState control = KeyState::Down;
            KeyState alt = KeyState::Down;
            KeyState shift = KeyState::Down;
            KeyState system = KeyState::Down;
        };

        struct Resize
        {
            uint32_t height = 0;
            uint32_t width = 0;
        };

        enum class Type
        {
            None,
            Focus,
            MouseButton,
            MouseMove,
            KeyBoard,
            Resize,
        };

        Type type = Type::None;
        std::variant<Focus, MouseButton, MouseMove, Keyboard, Resize> event{Focus{false}};
        // why isn't variant not default constructable?
    };
}