#ifndef WINDOW_H
#define WINDOW_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "piece.h"

class window
{
public:
    window(int, const std::string &);
    void draw(const std::vector<std::vector<std::shared_ptr<piece>>> &);

public:
    std::unique_ptr<sf::RenderWindow> main_window;
    std::vector<sf::CircleShape> avaiable_moves;

private:
    std::vector<sf::RectangleShape> tiles;
};

#endif