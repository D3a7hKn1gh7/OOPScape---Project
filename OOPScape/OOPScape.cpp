#include <iostream>
#include "Game.h"

int main()
{
    const char* levels[] = {
        "levels/level1.txt",
        "levels/level2.txt",
        "levels/level3.txt",
        "levels/level4.txt"
    };

    int totalLevels = 4;

    try
    {
        for (int i = 0; i < totalLevels; ++i)
        {
            std::cout << "\n=== Level " << (i + 1) << " ===\n";

            Game game;
            game.loadLevel(levels[i]);
            game.run();

            if (!game.hasWon())
                break;

            if (i < totalLevels - 1)
                std::cout << "\nLevel " << (i + 1)
                << " complete! Proceeding to level " << (i + 2) << "...\n";
            else
                std::cout << "\n*** Congratulations! You completed all levels! ***\n";
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Fatal error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}