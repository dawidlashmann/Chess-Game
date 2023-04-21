#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <memory>
#include <utility>
#include <stdlib.h>
#include "board.h"

class game
{
public:
    game();
    virtual void begin();

protected:
    void user_input(std::pair<int, int> &, std::pair<int, int> &, color);

    bool turn(std::pair<int, int>, std::pair<int, int>, color);
    bool interpose(std::pair<int, int>, std::pair<int, int>) const;
    bool has_any_moves(color);
    bool rochade(std::pair<int, int>, color);
    bool stale_mate(color);
    bool draw_by_repetition(color);
    bool check_(std::pair<int, int>, std::pair<int, int>, color) const;
    bool is_move_legal(std::pair<int, int>, std::pair<int, int>, color) const;
    
protected:
    chess_board *game_board = new chess_board();
    color winner;
    int turn_number;
    std::vector<std::vector<char>> white_past_positions, black_past_positions;
};

#endif