#pragma once
#ifndef HERO_H
#define HERO_H

#include <string>
#include "Entity.h"

// Hero is the base class for the player character. Concrete roles
// (Knight, future Wizard, etc.) inherit and override useAbility(),
// extension point required by the assignment -
// a new hero type = a new class, without changing Game.
class Hero : public Entity
{
public:
    Hero(Point startPos, int hp)
        : Entity(startPos, hp) {
    }

    ~Hero() override = default;

    virtual bool useAbility() = 0;
    virtual void onTurnEnd() {}
    virtual bool isInvulnerable() const { return false; }
    virtual std::string roleName() const = 0;
};

#endif