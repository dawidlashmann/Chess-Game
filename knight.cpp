#include "knight.h"

bool knight::move(std::pair<int, int> target_tile, color enemy_c)
{
    int column_distance = abs(target_tile.first - current_tile.first);
    int row_distance = abs(target_tile.second - current_tile.second);
// only L-shaped move
    if (((column_distance == 1) && (row_distance == 2)) || ((column_distance == 2) && (row_distance == 1)))
    {
// can't capture it's own piece
        if (enemy_c != side)
        {
            return true;
        }
        return false;
    }
    return false;
}