#ifndef KING_H
#define KING_H

#include "piece.h"

class king : public piece
{
public:
    king(int column, int row, color c, char letter) : piece(column, row, c, letter){};

    virtual bool move(std::pair<int, int>, color) override;
};

#endif