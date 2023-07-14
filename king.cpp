#include "king.h"

bool king::move(std::pair<int, int> target_tile, color enemy_c)
{
    int column_distance = abs(target_tile.first - current_tile.first);
    int row_distance = abs(target_tile.second - current_tile.second);

    if (enemy_c == side)
    {
        return false;
    }

    if (row_distance == 0 && column_distance == 2 && moved == 0)
    {
        return true;
    }

    if (column_distance > 1 || row_distance > 1)
    {
        return false;
    }
    return true;
}