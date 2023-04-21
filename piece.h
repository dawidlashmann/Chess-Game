#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <utility>
#include <memory>

enum color
{
    empty = 0,
    white = 1,
    black = 2
};

inline std::istream &operator>>(std::istream &is, color &c)
{
    int a;
    is >> a;
    c = static_cast<color>(a);

    return is;
}

class piece
{
public:
    piece();
    piece(int a, int b, char c);
    piece(int, int, color, char);

    virtual bool move(std::pair<int, int>, color) = 0;

    virtual ~piece(){};

public:
    std::pair<int, int> current_tile;
    color side;
    char letter;
    bool moved;
};

#endif