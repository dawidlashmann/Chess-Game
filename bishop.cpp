#include "bishop.h"

bool bishop::move(std::pair<int, int> target_tile, color enemy_c)
{
    int column_distance = abs(target_tile.first - current_tile.first);
    int row_distance = abs(target_tile.second - current_tile.second);
//if 45deg diagonal
    if (column_distance == row_distance)
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