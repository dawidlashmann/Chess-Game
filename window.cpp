#include "window.h"

window::window(int size)
{
    main_window.setSize(sf::Vector2u(size, size));
    main_window.setTitle("Chess game");

    float size_of_tile = main_window.getSize().x / 8;
    for (int column = 0; column < 8; column++)
    {
        for (int row = 0; row < 8; row++)
        {
            sf::RectangleShape temp_rect;
            temp_rect.setSize(sf::Vector2f(size_of_tile, size_of_tile));
            sf::Color color = ((column + row) % 2 == 0) ? sf::Color::White : sf::Color::Black;
            temp_rect.setFillColor(color);
            temp_rect.setPosition(sf::Vector2f(size_of_tile * column, size_of_tile * row));
            tiles.push_back(temp_rect);
        }
    }
}

void window::draw(const std::vector<std::vector<std::shared_ptr<piece>>> &board)
{
    main_window.clear();

    for (auto tile : tiles)
    {
        main_window.draw(tile);
    }
    for (auto column : board)
    {
        for (auto piece : column)
        {
            main_window.draw(piece->texture);
        }
    }

    main_window.display();
}