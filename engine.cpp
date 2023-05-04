#include "engine.h"

void engine::begin()
{
    color turn_color = white;
    std::pair<int, int> current_tile, target_tile;
    bool move = false;
    bool game_ended = false;
    while (gui.main_window.isOpen())
    {
        if (game_ended)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                gui.main_window.close();
            }
            continue;
        }
        if (turn_color == side)
        {
            if (define_moves())
            {
                std::pair<std::pair<int, int>, std::pair<int, int>> ai_move;
                do
                {
                    ai_move = getMove();
                } while (!turn(ai_move.first, ai_move.second, side));

                if (check_for_end_game(turn_color))
                {
                    game_ended = true;
                }
                turn_color = (turn_color == white) ? black : white;
                float size_of_tile_x = gui.main_window.getSize().x / 8;
                float size_of_tile_y = gui.main_window.getSize().y / 8;
                (*game_board)[ai_move.second]->sprite.setPosition(sf::Vector2f(size_of_tile_x * (*game_board)[ai_move.second]->current_tile.first, size_of_tile_y * (*game_board)[ai_move.second]->current_tile.second));
            }
        }

        sf::Event event;
        while (gui.main_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                gui.main_window.close();
                break;
            }
            if (event.type == sf::Event::MouseButtonPressed && turn_color != this->side)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (user_click(current_tile, target_tile, turn_color, move))
                    {
                        if (turn(current_tile, target_tile, turn_color))
                        {
                            if (check_for_end_game(turn_color))
                            {
                                game_ended = true;
                            }
                            move = false;
                            gui.avaiable_moves.clear();
                            turn_color = (turn_color == white) ? black : white;
                            float size_of_tile_x = gui.main_window.getSize().x / 8;
                            float size_of_tile_y = gui.main_window.getSize().y / 8;
                            (*game_board)[target_tile]->sprite.setPosition(sf::Vector2f(size_of_tile_x * (*game_board)[target_tile]->current_tile.first, size_of_tile_y * (*game_board)[target_tile]->current_tile.second));
                        }
                    }
                }
            }
        }
        gui.draw_scene(game_board->board);
    }
    switch (winner)
    {
    case white:
        std::cout << "WHITE WON!!! - 1:0\n";
        break;
    case black:
        std::cout << "BLACK WON!!! - 0:1\n";
        break;
    case empty:
        std::cout << "DRAW!!! - 0.5:0.5\n";
        break;
    }
}

bool engine::define_moves()
{
    this->legal_moves.clear();
    for (auto column : game_board->board)
    {
        for (auto tile : column)
        {
            if (tile->side == this->side)
            {
                for (auto target_column : game_board->board)
                {
                    for (auto target_tile : target_column)
                    {
                        if (target_tile == tile)
                            continue;
                        if (is_move_legal(tile->current_tile, target_tile->current_tile, this->side))
                        {
                            std::pair<std::pair<int, int>, std::pair<int, int>> temp_move{tile->current_tile, target_tile->current_tile};
                            legal_moves.push_back(temp_move);
                        }
                    }
                }
            }
        }
    }
    return !legal_moves.empty();
}

std::pair<std::pair<int, int>, std::pair<int, int>> engine::getMove()
{
    srand((unsigned)time(NULL));
    int random_number = rand() % legal_moves.size();
    return legal_moves.at(random_number);
}

void engine::end()
{
    if (winner == side)
    {
        std::cout << "\nHAHAHA I WON AGAIN\n";
    }
    else if (winner == empty)
    {
        std::cout << "\nTHAT WAS SOMEWHAT OF A BATTLE\n";
    }
    else
    {
        std::cout << "\nGG VERY GOOD PLAYER YOU ARE!\n";
    }
}