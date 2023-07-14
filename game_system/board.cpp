#include "board.h"

chess_board::chess_board()
{
    board.reserve(8);
    for (int column = 0; column < 8; column++)
    {
        std::vector<std::shared_ptr<piece>> temp_column;
        temp_column.reserve(8);
        for (int row = 0; row < 8; row++)
        {
            temp_column.emplace_back(std::make_shared<blank>(column, row, empty, ' '));
        }
        board.push_back(temp_column);
    }
}

void chess_board::draw() const
{
    std::cout << "       A     B     C     D     E     F     G     H\n\n";
    for (int iLine = 0; iLine < 8; iLine++)
    {
        if (iLine % 2 == 0)
        {
            printLine(iLine, ' ', '*');
        }
        else
        {
            printLine(iLine, '*', ' ');
        }
    }
    std::cout << "\n\n";
}

void chess_board::printLine(int iLine, char iColor1, char iColor2) const
{
    for (int subLine = 0; subLine < 3; subLine++)
    {
        std::cout << ' ';
        if (subLine == 1)
        {
            std::cout << iLine + 1;
        }
        else
        {
            std::cout << ' ';
        }
        std::cout << "   ";
        for (int iPair = 0; iPair < 4; iPair++)
        {
            for (int subColumn = 0; subColumn < 5; subColumn++)
            {
                if (subColumn == 2 && subLine == 1)
                {
                    std::cout << ((board[iPair * 2][iLine]->letter != ' ') ? board[iPair * 2][iLine]->letter : iColor1);
                }
                else
                {
                    if ((subColumn == 1 || subColumn == 3) && subLine == 1 && (board[iPair * 2][iLine]->letter != ' '))
                    {
                        std::cout << ' ';
                    }
                    else
                    {
                        std::cout << iColor1;
                    }
                    if (subColumn == 4)
                        std::cout << ' ';
                }
            }
            for (int subColumn = 0; subColumn < 5; subColumn++)
            {
                if (subColumn == 2 && subLine == 1)
                {
                    std::cout << ((board[(iPair * 2) + 1][iLine]->letter != ' ') ? board[(iPair * 2) + 1][iLine]->letter : iColor2);
                }
                else
                {
                    if ((subColumn == 1 || subColumn == 3) && subLine == 1 && (board[(iPair * 2) + 1][iLine]->letter != ' '))
                    {
                        std::cout << ' ';
                    }
                    else
                    {
                        std::cout << iColor2;
                    }
                    if (subColumn == 4)
                        std::cout << ' ';
                }
            }
        }
        std::cout << '\n';
    }
}

void chess_board::setTile(std::shared_ptr<piece> pice)
{
    board[pice->current_tile.first][pice->current_tile.second] = pice;
}

std::pair<int, int> chess_board::getKingTile(color king_color)
{
    return ((king_color == white) ? white_king_tile : black_king_tile);
}

void chess_board::swapTiles(std::pair<int, int> curr_tile, std::pair<int, int> target_tile)
{
    board[target_tile.first][target_tile.second] = board[curr_tile.first][curr_tile.second];
    board[target_tile.first][target_tile.second]->current_tile = target_tile;
    board[curr_tile.first][curr_tile.second] = std::make_shared<blank>(curr_tile.first, curr_tile.second, empty, ' ');
    float width = board[target_tile.first][target_tile.second]->sprite.getLocalBounds().width;
    float height = board[target_tile.first][target_tile.second]->sprite.getLocalBounds().height;
    float scale_x = board[target_tile.first][target_tile.second]->sprite.getScale().x;
    float scale_y = board[target_tile.first][target_tile.second]->sprite.getScale().y;
    board[curr_tile.first][curr_tile.second]->setTexture("../chess/blank.png", width * -scale_x);
    board[curr_tile.first][curr_tile.second]->sprite.setColor(sf::Color(0, 0, 0, 0));
    board[curr_tile.first][curr_tile.second]->sprite.setPosition(width * -scale_x * curr_tile.first, height * -scale_y * curr_tile.second);
    board[target_tile.first][target_tile.second]->moved = 1;
}