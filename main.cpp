#include <iostream>
#include "game.h"
#include "board.h"
#include "engine.h"

int main()
{
    // game *game_ = new game();
    engine *game_ = new engine(black);
    game_->begin();

    delete game_;

    return 0;
}