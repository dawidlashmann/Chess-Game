#include "pawn.h"

bool pawn::move(std::pair<int, int> target_tile, color enemy_c){
    
    color enemy_color = (side == white) ? black : white;
//only same column or capturing on a diaognal with color check
    if((target_tile.first == current_tile.first && enemy_c == empty) || (((target_tile.first == current_tile.first + 1) || (target_tile.first == current_tile.first - 1)) && (enemy_c == enemy_color))){
//can't move backwards
        if((target_tile.second > current_tile.second && side == black) || (target_tile.second < current_tile.second && side == white)){
            return false;
        }
//first move case
        int num_of_tiles = abs(target_tile.second - current_tile.second);
        if(!moved && num_of_tiles == 2 && target_tile.first == current_tile.first){
            return true;
        }
//regular move
        if(num_of_tiles == 1){
            return true;
        }
    }
    return false;
}