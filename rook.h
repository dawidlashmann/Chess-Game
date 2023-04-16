#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class rook : public piece
{
public:
    rook(int column, int row, color c, char letter) : piece(column, row, c, letter){};

    virtual bool move(std::pair<int, int>, color) override;
};

#endif