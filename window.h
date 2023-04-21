#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include "game.h"

class window{
public:
    window(int, int);

private:
    std::unique_ptr<sf::RenderWindow> main_window;
    friend class game;
};

#endif