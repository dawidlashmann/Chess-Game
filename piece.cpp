#include "piece.h"

piece::piece(int column, int row, color side, char letter)
{
    current_tile.first = column;
    current_tile.second = row;
    this->side = side;
    this->letter = letter;
    moved = 0;
}

bool piece::setTexture(const std::string &filename, int size)
{
    if (!texture.loadFromFile(filename))
    {
        std::cout << "\nFailed to load the image\n";
        return false;
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
    if (size != 0)
        setSize(size);
    return true;
}

void piece::setSize(int newSize)
{
    sf::FloatRect rect = sprite.getGlobalBounds();
    float width = rect.width;
    float height = rect.height;
    float factor_y = newSize / height;
    float factor_x = newSize / width;
    sprite.setScale(sf::Vector2f(factor_x, factor_y));
}