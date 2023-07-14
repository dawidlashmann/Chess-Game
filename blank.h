#ifndef BLANK_H
#define BLANK_H

#include "piece.h"
#include <iostream>

class blank : public piece{
public:
    blank() : piece() {};
    blank(int a, int b, char i) : piece(a, b, i) {};

    virtual bool move(std::pair<int, int>, color) override { return 0; };

};




#endif