#include "Knight.h"

Knight::Knight(Point startPos, int hp, int duration)
    : Hero(startPos, hp), shieldDuration(duration), shieldTurnsLeft(0)
{
}

// Activates the shield for shieldDuration turns.
// If already active, refreshes the remaining turn count.
bool Knight::useAbility()
{
    shieldTurnsLeft = shieldDuration;
    return true;
}

// Called at the end of each turn to tick down the shield duration.
void Knight::onTurnEnd()
{
    if (shieldTurnsLeft > 0)
        --shieldTurnsLeft;
}

bool Knight::isInvulnerable() const
{
    return shieldTurnsLeft > 0;
}