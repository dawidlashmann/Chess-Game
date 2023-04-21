#include <iostream>
#include "game.h"
#include "board.h"
#include "engine.h"

int main()
{
    bool round;
    do
    {
        {
            bool mode;
            game *game_;
            engine *ai_player;
            std::cout << "Duo mode - 0\nSingle player mode - 1\n";
            std::cin >> mode;
            while (std::cin.fail())
            {
                std::cout << "Wrong input\nTry again\n";
                std::cin.clear();
                std::cin.ignore();
                std::cin >> mode;
                system("clear");
                // system("cls");
            }
            if (mode){
                system("clear");
                // system("cls");
                color side;
                std::cout << "What color do you want to play?\n"
                          << "1 - White\n2 - Black\n";
                std::cin >> side;
                while (std::cin.fail())
                {
                    std::cout << "Wrong input\nTry again\n";
                    std::cin.clear();
                    std::cin.ignore();
                    std::cin >> side;
                    system("clear");
                    // system("cls");
                }
                ai_player = new engine((side == white) ? black : white);
                game_ = ai_player;
            }
            game_->begin();
        }
        std::cout << "\nDO YOU WISH TO PLAY ANOTHER ROUND?" << '\n'
                  << "1 - yes" << '\n'
                  << "0 - no" << '\n';

        std::cin >> round;

        while (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore();
            system("clear");
            // system("cls");
            std::cout << "Wrong input!" << '\n'
                      << "Try again" << '\n';
            std::cout << "DO YOU WISH TO PLAY ANOTHER ROUND?" << '\n'
                      << "1 - yes" << '\n'
                      << "0 - no" << '\n';
            std::cin >> round;
        }

    } while (round);

    return 0;
}