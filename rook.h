#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

class rook : public piece
{
public:
    rook(int column, int row, color c, char letter, const std::string &filename = "", int size = 0) : piece(column, row, c, letter) { this->setTexture(filename, size); };

    virtual bool move(std::pair<int, int>, color) override;
};

#endif