#include "window.h"

void window::create_window(int windowSize, const std::string &windowName)
{
    main_window.create(sf::VideoMode(windowSize, windowSize), windowName, sf::Style::Close | sf::Style::Titlebar);
    main_window.setPosition(sf::Vector2i(500, 200));
    main_window.setVerticalSyncEnabled(false);
    main_window.setFramerateLimit(30);
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
    default_font.loadFromFile("../chess/arial.ttf");
}

void window::draw_scene(const std::vector<std::vector<std::shared_ptr<piece>>> &board)
{
    main_window.clear();
    sf::View view = main_window.getView();
    view.setRotation(180);
    main_window.setView(view);

    for (auto tile : tiles)
    {
        main_window.draw(tile);
    }
    for (auto column : board)
    {
        for (auto piece : column)
        {
            main_window.draw(piece->sprite);
        }
    }
    for (auto dot : avaiable_moves)
    {
        main_window.draw(dot);
    }
}

void window::draw_box(const std::string &text_to_be_drawn, sf::Vector2f size, sf::Vector2f position)
{
    sf::RectangleShape box;
    //box.setSize(sf::Vector2f(main_window.getSize().x / 2, main_window.getSize().y / 4));
    box.setSize(size);
    //box.setPosition(  );
    box.setPosition(position);
    box.setFillColor(sf::Color::Blue);
    sf::Text text;
    text.setFont(default_font);
    text.setString(text_to_be_drawn);
    text.setCharacterSize(35);
    text.setScale(-1.f, -1.f);
    text.setFillColor(sf::Color::White);
    text.setOrigin(sf::Vector2f(text.getLocalBounds().width / 2, text.getLocalBounds().height));
    text.setPosition(sf::Vector2f(main_window.getSize().x / 2, main_window.getSize().y / 2));
    main_window.draw(box);
    main_window.draw(text);
}