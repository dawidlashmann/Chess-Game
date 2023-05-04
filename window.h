#ifndef WINDOW_H
#define WINDOW_H

#include <memory>
#include <SFML/Graphics.hpp>
#include "piece.h"

class window
{
public:
    window(){};
    void create_window(int, const std::string &);
    void draw_scene(const std::vector<std::vector<std::shared_ptr<piece>>> &);
    void draw_box(const std::string &);

public:
    sf::RenderWindow main_window;
    std::vector<sf::CircleShape> avaiable_moves;

private:
    std::vector<sf::RectangleShape> tiles;
    sf::Font default_font;
    sf::Text text;
};

#endif