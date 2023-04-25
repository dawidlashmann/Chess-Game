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
    if (!temp_texture.loadFromFile(filename))
    {
        std::cout << "\nFailed to load the image\n";
        return false;
    }
    temp_texture.setSmooth(true);
    texture.setTexture(temp_texture);
    return true;
}

void piece::setSize(int newSize)
{
    sf::FloatRect rect = texture.getLocalBounds();
    float width = rect.width;
    float factor = width / newSize;
    texture.setScale(sf::Vector2f(factor, factor));
}