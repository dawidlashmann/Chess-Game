#ifndef BOARD_H
#define BOARD_H

#include "piece.h"
#include "pawn.h"
#include "rook.h"
#include "bishop.h"
#include "queen.h"
#include "knight.h"
#include "king.h"
#include "blank.h"
#include <memory>
#include <vector>

class chess_board
{
public:
    chess_board();
    void draw() const;

private:
    void printLine(int, char, char) const;

public:
    void setTile(std::shared_ptr<piece>);
    std::pair<int, int> getKingTile(color);
    void swapTiles(std::pair<int, int>, std::pair<int, int>);

    inline std::shared_ptr<piece> &
    operator[](const std::pair<int, int> &tile)
    {
        return board[tile.first][tile.second];
    }

public:
    std::vector<std::vector<std::shared_ptr<piece>>> board;
    std::pair<int, int> white_king_tile, black_king_tile;
};

#endif