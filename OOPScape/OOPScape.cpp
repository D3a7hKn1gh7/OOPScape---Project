#include <iostream>
#include "Game.h"

int main(int argc, char* argv[])
{
    std::string levelFile = "levels/level1.txt";
    if (argc > 1)
        levelFile = argv[1];

    try
    {
        Game game;
        game.loadLevel(levelFile);
        game.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Fatal error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}