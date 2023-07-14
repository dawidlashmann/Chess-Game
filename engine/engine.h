#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <chrono>
#include <thread>
#include "game.h"

class engine : public game
{
public:
    engine(color c) : game() { side = c; };
    virtual void begin() override;

private:
    bool define_moves();
    std::pair<std::pair<int, int>, std::pair<int, int>> getMove();

    int exchange(std::pair<int, int>, std::pair<int, int>, int, color);
    int visibility(std::pair<int, int>, std::pair<int, int>);

private:
    color side;
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> legal_moves;
};

#endif