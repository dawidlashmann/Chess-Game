#include "game.h"

game::game()
{
    game_board = new chess_board();
    int windowSize = 504;
    int tile_size = windowSize / 8;
    gui.create_window(windowSize, "Chess game");
    turn_number = 1;

    // board initialization
    //  pawns
    for (int j = 0; j < 8; j++)
    {
        game_board->setTile(std::make_shared<pawn>(j, 1, white, 'P', "chess/Chess_plt60.png", tile_size));
    }
    for (int j = 0; j < 8; j++)
    {
        game_board->setTile(std::make_shared<pawn>(j, 6, black, 'p', "chess/Chess_pdt60.png", tile_size));
    }

    // queen
    game_board->setTile(std::make_shared<queen>(3, 0, white, 'Q', "chess/Chess_qlt60.png", tile_size));
    game_board->setTile(std::make_shared<queen>(3, 7, black, 'q', "chess/Chess_qdt60.png", tile_size));

    // bishops
    game_board->setTile(std::make_shared<bishop>(2, 0, white, 'B', "chess/Chess_blt60.png", tile_size));
    game_board->setTile(std::make_shared<bishop>(5, 0, white, 'B', "chess/Chess_blt60.png", tile_size));
    game_board->setTile(std::make_shared<bishop>(2, 7, black, 'b', "chess/Chess_bdt60.png", tile_size));
    game_board->setTile(std::make_shared<bishop>(5, 7, black, 'b', "chess/Chess_bdt60.png", tile_size));

    // knights
    game_board->setTile(std::make_shared<knight>(1, 0, white, 'N', "chess/Chess_nlt60.png", tile_size));
    game_board->setTile(std::make_shared<knight>(6, 0, white, 'N', "chess/Chess_nlt60.png", tile_size));
    game_board->setTile(std::make_shared<knight>(1, 7, black, 'n', "chess/Chess_ndt60.png", tile_size));
    game_board->setTile(std::make_shared<knight>(6, 7, black, 'n', "chess/Chess_ndt60.png", tile_size));

    // rooks
    game_board->setTile(std::make_shared<rook>(0, 0, white, 'R', "chess/Chess_rlt60.png", tile_size));
    game_board->setTile(std::make_shared<rook>(7, 0, white, 'R', "chess/Chess_rlt60.png", tile_size));
    game_board->setTile(std::make_shared<rook>(0, 7, black, 'r', "chess/Chess_rdt60.png", tile_size));
    game_board->setTile(std::make_shared<rook>(7, 7, black, 'r', "chess/Chess_rdt60.png", tile_size));

    // kings
    game_board->setTile(std::make_shared<king>(4, 0, white, 'K', "chess/Chess_klt60.png", tile_size));
    game_board->setTile(std::make_shared<king>(4, 7, black, 'k', "chess/Chess_kdt60.png", tile_size));
    game_board->white_king_tile.first = 4;
    game_board->white_king_tile.second = 0;
    game_board->black_king_tile.first = 4;
    game_board->black_king_tile.second = 7;

    for (auto column : game_board->board)
    {
        for (auto piece : column)
        {
            piece->sprite.setPosition(sf::Vector2f(tile_size * piece->current_tile.first, tile_size * piece->current_tile.second));
        }
    }
    for (auto column : game_board->board)
    {
        for (auto tile : column)
        {
            if (tile->side == empty)
            {
                tile->setTexture("chess/blank.png", tile_size);
                tile->sprite.setColor(sf::Color(0, 0, 0, 0));
            }
        }
    }
}

void game::begin()
{
    color turn_color = white;
    std::pair<int, int> current_tile, target_tile;
    bool move = false;
    bool game_ended = false;
    while (gui.main_window.isOpen())
    {
        sf::Event event;
        while (gui.main_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                gui.main_window.close();
                break;
            }
            if (event.type == sf::Event::MouseButtonPressed && !game_ended)
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
                gui.draw_box(winner_str + "won");
            }
            else
            {
                gui.draw_box("It's a draw");
            }
        }
        gui.main_window.display();
    }
}

bool game::user_click(std::pair<int, int> &current_tile, std::pair<int, int> &target_tile, const color &c, bool &move)
{
    sf::Vector2f mouse = gui.main_window.mapPixelToCoords(sf::Mouse::getPosition(gui.main_window));
    std::shared_ptr<piece> this_tile = std::make_shared<blank>(-1, -1, empty, ' ');
    for (auto column : game_board->board)
    {
        for (auto tile : column)
        {
            if (tile->side == empty && move == 0)
                continue;
            sf::FloatRect bounds = tile->sprite.getGlobalBounds();
            if (bounds.contains(mouse))
            {
                this_tile = tile;
            }
        }
    }
    if (this_tile->current_tile.first == -1)
    {
        return false;
    }

    if (this_tile->side == c)
    {
        gui.avaiable_moves.clear();
        for (auto column : game_board->board)
        {
            for (auto tile : column)
            {
                if (is_move_legal(this_tile->current_tile, tile->current_tile, c))
                {
                    int tile_size = gui.main_window.getSize().x / 8;
                    sf::CircleShape dot(tile_size / 4, 60);
                    dot.setOrigin(sf::Vector2f(tile_size / 4, tile_size / 4));
                    dot.setPosition(sf::Vector2f(tile->current_tile.first * tile_size + tile_size / 2, tile->current_tile.second * tile_size + tile_size / 2));
                    dot.setFillColor(sf::Color(169, 169, 169, 150));
                    gui.avaiable_moves.push_back(dot);
                }
            }
        }
        current_tile = this_tile->current_tile;
        move = true;
        return false;
    }
    else if (move)
    {
        target_tile = this_tile->current_tile;
        return true;
    }
    return false;
}

bool game::turn(std::pair<int, int> current_tile, std::pair<int, int> target_tile, color c)
{
    // legal move check
    if (is_move_legal(current_tile, target_tile, c))
    {
        if ((*game_board)[target_tile]->letter != ' ')
        {
            black_past_positions.clear();
            white_past_positions.clear();
        }
        // if king is moved
        if ((*game_board)[current_tile]->letter == 'K' || (*game_board)[current_tile]->letter == 'k')
        {
            // see if the user wants to perform an rochade
            // if yes, the move is perfomed inside the rochade function thus the return statement
            if (abs(target_tile.first - current_tile.first) == 2)
            {
                return rochade(target_tile, c);
            }

            std::pair<int, int> &king_tile = (c == white) ? game_board->white_king_tile : game_board->black_king_tile;
            king_tile = target_tile;
        }
        // actual move
        game_board->swapTiles(current_tile, target_tile);

        // promotion
        if ((*game_board)[target_tile]->letter == 'P' || (*game_board)[target_tile]->letter == 'p')
        {
            char temp_letter = (c == white) ? 'Q' : 'q';
            const std::string temp_filename = (c == white) ? "chess/Chess_qlt60.png" : "chess/Chess_qdt60.png";
            if (target_tile.second == 7 || target_tile.second == 0)
                (*game_board)[target_tile] = std::make_shared<queen>(target_tile.first, target_tile.second, c, temp_letter, temp_filename, gui.main_window.getSize().x / 8);
            black_past_positions.clear();
            white_past_positions.clear();
        }

        return true;
    }
    return false;
}

bool game::rochade(std::pair<int, int> target_tile, color c)
{
    std::pair<int, int> &king_tile = (c == white) ? game_board->white_king_tile : game_board->black_king_tile;
    std::pair<int, int> rook;
    bool long_rochade = ((target_tile.first - king_tile.first) < 0) ? 1 : 0;
    int iter;

    if (long_rochade)
    {
        rook.first = 0;
        rook.second = king_tile.second;
        iter = -1;
    }
    else
    {
        rook.first = 7;
        rook.second = king_tile.second;
        iter = 1;
    }

    if ((*game_board)[rook]->letter != 'R' && (*game_board)[rook]->letter != 'r')
    {
        return false;
    }

    if (!(*game_board)[rook]->moved)
    {
        if (!interpose(rook, king_tile))
        {
            for (int i = 0; i < 3; i++)
            {
                std::pair<int, int> king_tile_copy = king_tile;
                king_tile_copy.first += i * iter;
                if (check_(king_tile, king_tile_copy, c))
                {
                    return false;
                }
            }
            game_board->swapTiles(king_tile, target_tile);
            king_tile = target_tile;
            target_tile.first -= iter;
            game_board->swapTiles(rook, target_tile);

            return true;
        }
    }
    return false;
}

bool game::stale_mate(color c)
{
    for (auto column : game_board->board)
    {
        for (auto tile : column)
        {
            if (tile->side != c)
                continue;
            // if the piece is a knight, then define the tiles by hand...
            if (tile->side == 'N' || tile->side == 'n')
            {
                int col = tile->current_tile.first;
                int row = tile->current_tile.second;
                std::vector<std::pair<int, int>> knight_moves{{col - 1, row - 2}, {col + 1, row - 2}, {col - 2, row + 1}, {col - 2, row - 1}, {col + 2, row + 1}, {col + 2, row + 1}, {col - 1, row + 2}, {col + 1, row + 2}};
                for (auto move : knight_moves)
                {
                    if (move.first < 0 || move.first > 7 || move.second < 0 || move.second > 7)
                        continue;
                    if (is_move_legal(tile->current_tile, move, c))
                        return false;
                }
            }
            else
            {
                for (int column_iter = -1; column_iter <= 1; column_iter++)
                {
                    for (int row_iter = -1; row_iter <= 1; row_iter++)
                    {
                        int column = tile->current_tile.first + column_iter;
                        int row = tile->current_tile.second + row_iter;
                        if (column < 0 || column > 7 || row < 0 || row > 7)
                            continue;

                        std::pair<int, int> temp_tile{column, row};
                        if (is_move_legal(tile->current_tile, temp_tile, c))
                        {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

bool game::draw_by_repetition(color c)
{
    std::vector<char> current_board;

    for (auto column : game_board->board)
    {
        for (auto tile : column)
        {
            current_board.push_back(tile->letter);
        }
    }

    std::vector<std::vector<char>> &past_positions = (c == white) ? white_past_positions : black_past_positions;

    int board_occurence = 0;
    for (auto past_position : past_positions)
    {
        if (past_position == current_board)
            board_occurence++;

        if (board_occurence == 2)
            return true;
    }

    past_positions.push_back(current_board);
    return false;
}

bool game::interpose(std::pair<int, int> current_tile, std::pair<int, int> target_tile) const
{
    // knight can't be interposed
    if ((*game_board)[current_tile]->letter != 'N' && (*game_board)[current_tile]->letter != 'n')
    {
        // determine iterators
        int column_iter = (target_tile.first > current_tile.first) ? 1 : -1;
        int row_iter = (target_tile.second > current_tile.second) ? 1 : -1;
        if (target_tile.first == current_tile.first)
            column_iter = 0;
        if (target_tile.second == current_tile.second)
            row_iter = 0;
        current_tile.first += column_iter;
        current_tile.second += row_iter;

        // iterate till reaches the target tile or a piece
        while (current_tile != target_tile)
        {
            if ((*game_board)[current_tile]->letter != ' ')
            {
                return true;
            }
            current_tile.first += column_iter;
            current_tile.second += row_iter;
        }
    }
    return false;
}

bool game::has_any_moves(color king_color)
{
    color enemy_color = (king_color == white) ? black : white;
    std::pair<int, int> king_tile = (king_color == white) ? game_board->white_king_tile : game_board->black_king_tile;

    bool can_king_move = 0;
    for (int column = -1; column <= 1; column++)
    {
        for (int row = -1; row <= 1; row++)
        {
            int temp_column = king_tile.first + column;
            int temp_row = king_tile.second + row;
            if (temp_column >= 0 && temp_column <= 7 && temp_row >= 0 && temp_row <= 7)
            {
                std::pair<int, int> temp_target_tile{temp_column, temp_row};
                if ((*game_board)[king_tile]->move(temp_target_tile, (*game_board)[temp_target_tile]->side))
                {
                    if (!check_(king_tile, temp_target_tile, king_color))
                    {
                        // if the king can move we return true as we don't have to determine if we can block the check
                        can_king_move = 1;
                        return true;
                    }
                }
            }
        }
    }
    // determine the checking piece
    bool can_block_check = 0;
    std::pair<int, int> checking_tile{-1, -1};
    for (auto column : game_board->board)
    {
        for (auto checking_tile_ : column)
        {
            if (checking_tile_->side == enemy_color)
            {
                if (checking_tile_->move(king_tile, king_color))
                {
                    if (!interpose(checking_tile_->current_tile, king_tile))
                    {
                        // can't block if there are more than one checking pieces (eg. discovery check)
                        // if the king can't move and there are more than one checking piece, it's MATE
                        if (checking_tile.first != -1)
                            return false;
                        checking_tile = checking_tile_->current_tile;
                    }
                }
            }
        }
    }

    // determine the iterators
    int column_iter = (king_tile.first > checking_tile.first) ? 1 : -1;
    int row_iter = (king_tile.second > checking_tile.second) ? 1 : -1;
    if (king_tile.first == checking_tile.first)
        column_iter = 0;
    if (king_tile.second == checking_tile.second)
        row_iter = 0;

    // check if any white piece can interpose on any tile between the checking piece and the king
    // (or capture the piece)
    while (checking_tile != king_tile)
    {
        for (auto column : game_board->board)
        {
            for (auto tile : column)
            {
                if (is_move_legal(tile->current_tile, checking_tile, king_color))
                {
                    if (tile->letter != 'K' && tile->letter != 'k')
                    {
                        can_block_check = 1;
                        break;
                    }
                }
            }
            if (can_block_check)
                break;
        }
        checking_tile.first += column_iter;
        checking_tile.second += row_iter;

        if (can_block_check)
            break;
    }
    // if can't block the check(or capture) or can't move the king it's mate
    if (can_block_check == 0 && can_king_move == 0)
    {
        return false;
    }
    return true;
}

bool game::is_move_legal(const std::pair<int, int> current_tile, const std::pair<int, int> target_tile, const color c) const
{
    if ((*game_board)[current_tile]->side != c)
        return false;
    if (!(*game_board)[current_tile]->move(target_tile, (*game_board)[target_tile]->side))
        return false;
    if (interpose(current_tile, target_tile))
        return false;
    if (check_(current_tile, target_tile, c))
        return false;

    return true;
}

bool game::check_(std::pair<int, int> current_tile, std::pair<int, int> target_tile, color king_color) const
{
    color enemy_color = (king_color == white) ? black : white;
    std::pair<int, int> king_tile = game_board->getKingTile(king_color);

    // temporarly change to the desired position
    if ((*game_board)[current_tile]->letter == 'K' || (*game_board)[current_tile]->letter == 'k')
    {
        king_tile = target_tile;
    }
    std::shared_ptr<piece> current_tile_copy = (*game_board)[current_tile];
    std::shared_ptr<piece> target_tile_copy = (*game_board)[target_tile];
    (*game_board)[current_tile] = std::make_shared<blank>(current_tile.first, current_tile.second, empty, ' ');
    // target_tile has to be set after current_tile (to see if there is a check)
    (*game_board)[target_tile] = current_tile_copy;

    // traverse throught the board
    for (auto column : game_board->board)
    {
        for (auto tile : column)
        {
            // check if an enemy piece can go to the king's tile
            if (tile->side == enemy_color)
            {
                if (tile->move(king_tile, king_color))
                {
                    if (!interpose(tile->current_tile, king_tile))
                    {
                        // swap back to the original board
                        (*game_board)[current_tile] = current_tile_copy;
                        (*game_board)[target_tile] = target_tile_copy;
                        return true;
                    }
                }
            }
        }
    }
    // swap back to the original board
    (*game_board)[current_tile] = current_tile_copy;
    (*game_board)[target_tile] = target_tile_copy;
    return false;
}

bool game::check_for_end_game(color c)
{
    color enemy_color = (c == white) ? black : white;
    std::pair<int, int> enemy_king_tile = (c == white) ? game_board->black_king_tile : game_board->white_king_tile;
    if (check_(enemy_king_tile, enemy_king_tile, enemy_color))
    {
        if (!has_any_moves(enemy_color))
        {
            winner = c;
            return true;
        }
    }
    else if (stale_mate(enemy_color))
    {
        winner = empty;
        return true;
    }

    if (draw_by_repetition(c))
    {
        winner = empty;
        return true;
    }

    return false;
}