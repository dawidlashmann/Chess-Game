#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

class queen : public piece
{
public:
    queen(int column, int row, color c, char letter) : piece(column, row, c, letter){};

    virtual bool move(std::pair<int, int>, color) override;
};

#endif