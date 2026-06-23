#pragma once
#ifndef KNIGHT_H
#define KNIGHT_H

#include "Hero.h"

// Knight is a hero whose special ability (command "OOP") is a
// temporary shield - full invulnerability for a number of turns.
class Knight : public Hero
{
public:
    Knight(Point startPos, int hp, int shieldDuration);

    bool useAbility() override;
    void onTurnEnd() override;
    bool isInvulnerable() const override;
    std::string roleName() const override { return "Knight"; }

private:
    int shieldDuration;
    int shieldTurnsLeft;
};

#endif