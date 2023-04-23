#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>


class window{
public:
    window(int);


private:
    std::unique_ptr<sf::RenderWindow> main_window;
    std::vector<sf::RectangleShape> tiles;
};

#endif