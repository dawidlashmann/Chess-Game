#include "engine.h"

void engine::begin()
{
    color turn_color = white;
    std::pair<int, int> current_tile, target_tile;
    bool move = false;
    bool game_ended = false;
    while (gui.main_window.isOpen())
    {
        if (turn_color == side)
        {
            if (define_moves())
            {
                std::pair<std::pair<int, int>, std::pair<int, int>> ai_move;
                ai_move = getMove();

                if (turn(ai_move.first, ai_move.second, side))
                {
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
        }

        sf::Event event;
        while (gui.main_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                gui.main_window.close();
                break;
            }
            if (event.type == sf::Event::MouseButtonPressed && turn_color != this->side && !game_ended)
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
        if (game_ended)
        {
            if (winner != empty)
            {
                std::string winner_str = (winner = white) ? "White " : "Black ";
                gui.draw_box(winner_str + "won", sf::Vector2f(gui.main_window.getSize().x / 2, gui.main_window.getSize().y / 4), sf::Vector2f(gui.main_window.getSize().x / 4, 3 * gui.main_window.getSize().y / 8));
            }
            else
            {
                gui.draw_box("It's a draw", sf::Vector2f(gui.main_window.getSize().x / 2, gui.main_window.getSize().y / 4), sf::Vector2f(gui.main_window.getSize().x / 4, 3 * gui.main_window.getSize().y / 8));
            }
        }
        gui.main_window.display();
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
    std::pair<std::pair<int, int>, std::pair<int, int>> best_move;
    int biggest_score = 0;
    for (auto move : legal_moves)
    {
        int8_t score = exchange(move.first, move.second, 5, this->side) + visibility(move.first, move.second);
        if (score > biggest_score)
        {
            biggest_score = score;
            best_move = move;
        }
    }
    return best_move;
}

int engine::exchange(std::pair<int, int> current_tile, std::pair<int, int> target_tile, int depth, color c)
{
    std::shared_ptr<piece> current_tile_copy = (*game_board)[current_tile];
    std::shared_ptr<piece> target_tile_copy = (*game_board)[target_tile];
    (*game_board)[current_tile] = std::make_shared<blank>(current_tile.first, current_tile.second, empty, ' ');
    (*game_board)[target_tile] = current_tile_copy;
    std::pair<int, int> king_tile_copy = (c == white) ? game_board->white_king_tile : game_board->black_king_tile;
    std::pair<int, int> &king_tile = (c == white) ? game_board->white_king_tile : game_board->black_king_tile;
    king_tile = target_tile;

    color enemy_c = (c == white) ? black : white;
    int worst_score = 0;

    if (depth < 0)
        return 0;

    for (auto column : game_board->board)
    {
        for (auto tile : column)
        {
            if (tile->side == enemy_c)
            {
                if (is_move_legal(tile->current_tile, target_tile, enemy_c))
                {
                    int score = 0;
                    int enemy_value = (this->side == tile->side) ? (*game_board)[target_tile]->value : tile->value;
                    int my_value = (enemy_value == tile->value) ? (*game_board)[target_tile]->value : tile->value;
                    score += (my_value - enemy_value) + exchange(tile->current_tile, target_tile, depth - 1, enemy_c);
                    if (score < worst_score)
                    {
                        worst_score = score;
                    }
                }
            }
        }
    }
    (*game_board)[current_tile] = current_tile_copy;
    (*game_board)[target_tile] = target_tile_copy;
    king_tile = king_tile_copy;
    return worst_score;
}

int engine::visibility(std::pair<int, int> current_tile, std::pair<int, int> target_tile)
{
    std::shared_ptr<piece> current_tile_copy = (*game_board)[current_tile];
    std::shared_ptr<piece> target_tile_copy = (*game_board)[target_tile];
    (*game_board)[current_tile] = std::make_shared<blank>(current_tile.first, current_tile.second, empty, ' ');
    (*game_board)[target_tile] = current_tile_copy;
    std::pair<int, int> king_tile_copy = (this->side == white) ? game_board->white_king_tile : game_board->black_king_tile;
    std::pair<int, int> &king_tile = (this->side == white) ? game_board->white_king_tile : game_board->black_king_tile;
    king_tile = target_tile;

    int my_score = 0;
    int enemy_score = 0;

    color enemy_c = (this->side == white) ? black : white;

    for (auto column : game_board->board)
    {
        for (auto tile : column)
        {
            if (this->side == tile->side)
            {
                for (auto column_ : game_board->board)
                {
                    for (auto tile_ : column)
                    {
                        if (tile->current_tile == tile_->current_tile)
                            continue;
                        if (is_move_legal(tile->current_tile, tile_->current_tile, this->side))
                        {
                            my_score++;
                        }
                    }
                }
            }
            else if (tile->side == enemy_c)
            {
                for (auto column_ : game_board->board)
                {
                    for (auto tile_ : column)
                    {
                        if (tile->current_tile == tile_->current_tile)
                            continue;
                        if (is_move_legal(tile->current_tile, tile_->current_tile, this->side))
                        {
                            enemy_score++;
                        }
                    }
                }
            }
        }
    }
    (*game_board)[current_tile] = current_tile_copy;
    (*game_board)[target_tile] = target_tile_copy;
    king_tile = king_tile_copy;
    return 0.5 * (my_score - enemy_score);
}
