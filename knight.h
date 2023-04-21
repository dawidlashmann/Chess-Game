#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class knight : public piece
{
public:
    knight(int column, int row, color c, char letter) : piece(column, row, c, letter){};

    virtual bool move(std::pair<int, int>, color) override;
    
};

#endif