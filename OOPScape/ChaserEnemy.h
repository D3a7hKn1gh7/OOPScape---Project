#pragma once
#ifndef CHASER_ENEMY_H
#define CHASER_ENEMY_H

#include "Enemy.h"

// ChaserEnemy moves toward the hero each turn using BFS pathfinding,
// always taking the shortest available path.
class ChaserEnemy : public Enemy
{
public:
    explicit ChaserEnemy(Point startPos)
        : Enemy(startPos) {
    }

    void moveTowards(const Point& heroPos, const Board& board) override;
};

#endif