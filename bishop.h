#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class bishop : public piece
{
public:
    bishop(int column, int row, color c, char letter) : piece(column, row, c, letter){};

    virtual bool move(std::pair<int, int>, color) override;
};

#endif