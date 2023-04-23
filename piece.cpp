#include "piece.h"

piece::piece(int column, int row, color side, char letter)
{
    current_tile.first = column;
    current_tile.second = row;
    this->side = side;
    this->letter = letter;
    moved = 0;
}

bool piece::setTexture(const std::string &filename)
{
    sf::Texture temp_texture;
    temp_texture.loadFromFile(filename);
    texture.setTexture(temp_texture);
}