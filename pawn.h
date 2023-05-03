#ifndef PAWN_H
#define PAWN_H

#include <iostream>
#include "piece.h"



class pawn : public piece{
public:
    pawn(int column, int row, color c, char letter, const std::string &filename = "", int size = 0) : piece(column, row, c, letter) { this->setTexture(filename, size); };

    virtual bool move(std::pair<int, int>, color) override;
};



#endif