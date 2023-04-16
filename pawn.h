#ifndef PAWN_H
#define PAWN_H

#include <iostream>
#include "piece.h"



class pawn : public piece{
public:
    pawn(int column, int row, color c, char letter) : piece(column, row, c, letter) {};

    virtual bool move(std::pair<int, int>, color) override;
    
public:
    bool moved;
};



#endif