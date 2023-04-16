#include "rook.h"

bool rook::move(std::pair<int, int> target_tile, color enemy_c)
{
//the same row or column
    if ((target_tile.first == current_tile.first) || (target_tile.second == current_tile.second))
    {
//can't capture it's own pieces
        if (enemy_c != side)
        {
            return true;
        }
        return false;
    }
    return false;
}