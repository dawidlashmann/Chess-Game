#include "window.h"

window::window(int width, int height)
{
    main_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height), "Chess game");
    main_window->setSize(sf::Vector2u(width, height));
}