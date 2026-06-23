#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
#include "Board.h"

// Enemy is the base class for all enemies in the game.
// Derived classes implement moveTowards() to define movement behavior.
class Enemy : public Entity
{
public:
    Enemy(Point startPos)
        : Entity(startPos, 1) {
    }

    ~Enemy() override = default;

    // Moves the enemy one step. heroPos is the current hero position,
    // board is used to check walkability.
    virtual void moveTowards(const Point& heroPos, const Board& board) = 0;
};

#endif