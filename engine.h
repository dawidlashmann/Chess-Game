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

private:
    virtual void begin() override;
    bool define_moves();
    std::pair<std::pair<int, int>, std::pair<int, int>> getMove();
    void end();

public:
    color side;
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> legal_moves;
};

#endif