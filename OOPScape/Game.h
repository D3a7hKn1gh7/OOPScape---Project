#pragma once
#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>
#include "Board.h"
#include "Hero.h"
#include "Enemy.h"
#include "Trap.h"

// Game manages the main turn loop: rendering the board, reading player
// commands, moving the hero and enemies, and checking win/lose conditions.
class Game
{
public:
    Game();

    void loadLevel(const std::string& filename);
    void run();
    bool hasWon() const { return playerWon; }

private:
    Board board;
    std::unique_ptr<Hero> hero;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<Trap> traps;
    std::vector<std::vector<bool>> explored;

    bool gameOver = false;
    bool playerWon = false;

    int fogRadius = 3;

    void printBoard() const;
    void updateFog();
    void processCommand(char command);
    void moveHero(int dx, int dy);
    void moveEnemies();
    void checkHeroAgainstTrap();
    bool checkWinCondition() const;
    bool checkLoseCondition() const;
};

#endif