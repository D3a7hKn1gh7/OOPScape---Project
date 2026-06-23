#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include "Point.h"

// Entity is the abstract base class for everything that moves on the board
// (hero and enemies). Defines the common interface - position and health.
class Entity
{
public:
    Entity(Point startPos, int hp)
        : position(startPos), health(hp) {
    }

    virtual ~Entity() = default;

    Point getPosition() const { return position; }
    void setPosition(Point p) { position = p; }

    int getHealth() const { return health; }
    bool isAlive() const { return health > 0; }

    // Reduces health by the given amount (does not go below 0).
    void takeDamage(int amount)
    {
        health -= amount;
        if (health < 0)
            health = 0;
    }

protected:
    Point position;
    int health;
};

#endif