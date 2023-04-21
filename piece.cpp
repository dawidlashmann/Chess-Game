#include "piece.h"


piece::piece(int column, int row, color side, char letter){
    current_tile.first = column;
    current_tile.second = row;
    this->side = side;
    this->letter = letter;
    moved = 0;
}

piece::piece(int column, int row, char letter){
    current_tile.first = column;
    current_tile.second = row;
    this -> letter = letter;
    moved = 0;
}