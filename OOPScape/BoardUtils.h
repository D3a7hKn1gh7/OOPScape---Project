#pragma once
#ifndef BOARD_UTILS_H
#define BOARD_UTILS_H

#include "Board.h"

// Helper function required by the BFS chasing function.
// Returns true if cell (x, y) is within board bounds and is not a wall.
inline bool isWalkable(int x, int y, const Board& board)
{
    if (!board.isInside(x, y))
        return false;
    char c = board.at(x, y);
    return c != '*';
}

#endif