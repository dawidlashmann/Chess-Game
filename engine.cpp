#include "engine.h"

void engine::begin()
{
    // game loop
    while (true)
    {
        // white's turn
        std::pair<int, int> current_tile, target_tile;
        std::pair<std::pair<int, int>, std::pair<int, int>> engine_move;
        do
        {
            system("clear");
            // system("cls");
            game_board->draw();
            std::cout << "Turn number: " << turn_number << '\n';
            std::cout << "White's turn:\n";
            if (this->side == white)
            {
                std::cout << "Thinking...\n"
                          << std::flush;
                
                if(!define_moves())
                    break;
                engine_move = getMove();
                current_tile = engine_move.first;
                target_tile = engine_move.second;
                //std::this_thread::sleep_for(std::chrono::milliseconds(3000));
                std::cout << '\n'
                          << (char)(engine_move.first.first + 97) << '\n'
                          << engine_move.first.second + 1 << '\n'
                          << (char)(engine_move.second.first + 97) << '\n'
                          << engine_move.second.second + 1 << '\n';
                std::cin.ignore();
                std::cout << "\nPress Enter to continue\n";
                std::cin.get();
            }
            else
            {
                bool siema;
                user_click(current_tile, target_tile, white, siema);    
            }

        } while (!turn(current_tile, target_tile, white));

        // check if black is checked and if so, check if he has any moves
        if (check_(game_board->black_king_tile, game_board->black_king_tile, black))
        {
            if (!has_any_moves(black))
            {
                winner = white;
                break;
            }
        }
        else if (stale_mate(black))
        {
            // check after each move is it's stalemate
            winner = empty;
            break;
        }
        // check if it's a draw by repetition
        if (draw_by_repetition(white))
        {
            winner = empty;
            break;
        }

        // draw the board
        system("clear");
        // system("cls");
        game_board->draw();

        // black's turn
        do
        {
            system("clear");
            // system("cls");
            game_board->draw();
            std::cout << "Turn number: " << turn_number << '\n';
            std::cout << "Black's turn:\n";
            if (this->side == black)
            {
                std::cout << "Thinking..." << std::flush;
                
                if(!define_moves())
                    break;
                engine_move = getMove();
                current_tile = engine_move.first;
                target_tile = engine_move.second;
                //std::this_thread::sleep_for(std::chrono::milliseconds(3000));
                std::cout << '\n'
                          << (char)(engine_move.first.first + 97) << '\n'
                          << engine_move.first.second + 1 << '\n'
                          << (char)(engine_move.second.first + 97) << '\n'
                          << engine_move.second.second + 1 << '\n';
                std::cin.ignore();
                std::cout << "\nPress Enter to continue\n";
                std::cin.get();
            }
            else
            {
                bool siema;
                user_click(current_tile, target_tile, black, siema);
            }

        } while (!turn(current_tile, target_tile, black));

        // check if white is checked and if so, check if he has any moves
        if (check_(game_board->white_king_tile, game_board->white_king_tile, white))
        {
            if (!has_any_moves(white))
            {
                winner = black;
                break;
            }
        }
        else if (stale_mate(white))
        {
            // check for stalemate
            winner = empty;
            break;
        }
        // check draw by repetition
        if (draw_by_repetition(black))
        {
            winner = empty;
            break;
        }

        // draw the board
        system("clear");
        // system("cls");
        game_board->draw();

        turn_number++;
    }
    system("clear");
    // system("cls");
    game_board->draw();

    switch (winner)
    {
    case white:
        std::cout << "\nWHITE WON!!! - 1:0\n";
        break;
    case black:
        std::cout << "\nBLACK WON!!! - 0:1\n";
        break;
    case empty:
        std::cout << "\nDRAW!!! - 0.5:0.5\n";
        break;
    }
    end();
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