#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"

class bishop : public piece
{
public:
    bishop(int column, int row, color c, char letter, const std::string &filename = "", int size = 0) : piece(column, row, c, letter) { this->setTexture(filename, size); };

    virtual bool move(std::pair<int, int>, color) override;
};

#endif