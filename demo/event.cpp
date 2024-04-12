#include "M3L/Rendering/Target/RenderWindow.hpp"
#include "M3L/Rendering/Sprite.hpp"

#include <iostream>

int main()
{
    m3l::ThreadPool tp;
    m3l::RenderWindow window(tp, 300, 300, "title");
    m3l::Event event;

    window.subscribe<m3l::Event::Resize>([] (const m3l::Event::Resize &_resize) {
        std::cout << "Resize callback: { height: " << _resize.height << ", width: " << _resize.width << " }" << std::endl;
    });

    window.subscribe<m3l::Event::MouseButton>([] (const m3l::Event::MouseButton &_btn) {
        std::cout << "MouseButton callback: { button: " << _btn.button << ", state: " << _btn.state << " }" << std::endl;
    });

    window.subscribe<m3l::Event::MouseMove>([] (const m3l::Event::MouseMove &_mouse) {
        std::cout << "MouseMove callback: { x: " << _mouse.x << ", y: " << _mouse.y << " }" << std::endl;
    });

    window.subscribe<m3l::Event::Keyboard>([] (const m3l::Event::Keyboard &_kb) {
        std::cout << "Keyboard callback: { key: " << _kb.key << ", state: " << _kb.state << " { shift: " << _kb.shift << ", control: " << _kb.control << ", alt: " << _kb.alt << " } }" << std::endl;
    });

    window.subscribe<m3l::Event::Focus>([] (const m3l::Event::Focus& _focus) {
        std::cout << "Focus callback: { focus: " << _focus.state << " }" << std::endl;
    });

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            std::cout << "Event received into main thread: " << static_cast<int>(event.type) << std::endl;
        }
        window.clear();
        window.display();
    }
    return 0;
}