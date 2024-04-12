#include "M3L/Rendering/Target/RenderWindow.hpp"
#include "M3L/Rendering/Sprite.hpp"

int main()
{
    m3l::ThreadPool tp;
    m3l::RenderWindow window(tp, 300, 300, "title");
    m3l::Event event;
    m3l::Texture texture;
    m3l::Sprite sprite;

    texture.load("ressources/texture.bmp");
    sprite.setTexture(texture);
    sprite.setPosition(20.f, 50.f);
    while (window.isOpen()) {
        while (window.pollEvent(event)) {}
        window.clear();
        window.draw(sprite);
        window.display();
    }
    return 0;
}