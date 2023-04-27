#include "window.h"

window::window(int windowSize, const std::string &windowName)
{
    main_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(windowSize, windowSize), windowName);
    main_window->setVerticalSyncEnabled(false);
    main_window->setFramerateLimit(30);
    float size_of_tile = windowSize / 8;
    for (int column = 0; column < 8; column++)
    {
        for (int row = 0; row < 8; row++)
        {
            sf::RectangleShape temp_rect;
            temp_rect.setSize(sf::Vector2f(size_of_tile, size_of_tile));
            sf::Color color = ((column + row) % 2 == 0) ? sf::Color::White : sf::Color(222, 184, 135);
            temp_rect.setFillColor(color);
            temp_rect.setPosition(sf::Vector2f(size_of_tile * column, size_of_tile * row));
            tiles.push_back(temp_rect);
        }
    }
}

void window::draw(const std::vector<std::vector<std::shared_ptr<piece>>> &board)
{
    main_window->clear();

    float size_of_tile = main_window->getSize().x / 8;
    for (auto tile : tiles)
    {
        main_window->draw(tile);
    }
    for (auto column : board)
    {
        for (auto piece : column)
        {
            piece->sprite.setPosition(sf::Vector2f(size_of_tile * piece->current_tile.first, size_of_tile * piece->current_tile.second));
            main_window->draw(piece->sprite);
        }
    }
    for (auto dot : avaiable_moves)
    {
        main_window->draw(dot);
    }

    main_window->display();
}