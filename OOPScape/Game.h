#pragma once
#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>
#include "Board.h"
#include "Hero.h"
#include "Enemy.h"

// Game manages the main turn loop: rendering the board, reading player
// commands, moving the hero and enemies, and checking win/lose conditions.
class Game
{
public:
    Game();

    // Loads a level from a file and initializes the hero and enemies.
    void loadLevel(const std::string& filename);

    // Starts the main turn loop until win/lose/quit.
    void run();

private:
    Board board;
    std::unique_ptr<Hero> hero;
    std::vector<std::unique_ptr<Enemy>> enemies;

    bool gameOver = false;
    bool playerWon = false;

    void printBoard() const;
    void processCommand(char command);
    void moveHero(int dx, int dy);
    void moveEnemies();
    bool checkWinCondition() const;
    bool checkLoseCondition() const;
};

#endif