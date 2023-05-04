#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <utility>
#include <SFML/Graphics.hpp>
#include <stdio.h>

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
    piece(int, int, color, char);

    bool setTexture(const std::string &, int = 0);
    void setSize(int);
    virtual bool move(std::pair<int, int>, color) = 0;

    virtual ~piece(){};

public:
    std::pair<int, int> current_tile;
    color side;
    char letter;
    bool moved;
    sf::Texture texture;
    sf::Sprite sprite;
    uint8_t value;
};

#endif