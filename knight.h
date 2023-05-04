#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class knight : public piece
{
public:
    knight(int column, int row, color c, char letter, const std::string &filename = "", int size = 0) : piece(column, row, c, letter)
    {
        this->setTexture(filename, size);
        value = 3;
    };

    virtual bool move(std::pair<int, int>, color) override;
};

#endif