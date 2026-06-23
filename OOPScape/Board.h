#pragma once
#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>
#include "Point.h"

// Board holds the square map of a level (n x n characters),
// loaded and validated from a text file
//
// Allowed characters on the map:
//   '*' - wall (not walkable)
//   ' ' - path (walkable cell)
//   'S' - hero start position (exactly one)
//   'F' - exit (exactly one)
//   'E' - enemy start position (zero or more)
//   'T' - trap (zero or more) - extension beyond the base assignment
//
class Board
{
public:
    // Loads and validates a level from a file. On error, throws
    // std::runtime_error with a descriptive message (which row / what issue).
    void loadFromFile(const std::string& filename);
    int size() const { return n; }

    // Returns the character at cell (x, y). Out of bounds -> throws.
    char at(int x, int y) const;

    // Changes the content of a cell (e.g. when a hero/enemy moves
    // and the old position should become "path" again).
    void set(int x, int y, char value);

    Point getStartPosition() const { return startPos; }
    Point getExitPosition() const { return exitPos; }
    const std::vector<Point>& getEnemyPositions() const { return enemyPositions; }
    const std::vector<Point>& getTrapPositions() const { return trapPositions; }

    bool isInside(int x, int y) const;

private:
    int n = 0;
    std::vector<std::string> grid;

    Point startPos{ -1, -1 };
    Point exitPos{ -1, -1 };
    std::vector<Point> enemyPositions;
    std::vector<Point> trapPositions;

    static bool isAllowedChar(char c);
};

#endif