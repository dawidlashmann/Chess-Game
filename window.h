#ifndef WINDOW_H
#define WINDOW_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "piece.h"

class window
{
public:
    window(int);

    void draw(const std::vector<std::vector<std::shared_ptr<piece>>> &);

private:
    sf::RenderWindow main_window;
    std::vector<sf::RectangleShape> tiles;
};

#endif