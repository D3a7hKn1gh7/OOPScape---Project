#pragma once
#ifndef TRAP_H
#define TRAP_H

#include "Point.h"

// Trap represents a hazard placed on certain cells of the map (symbol 'T').
// When the hero steps on a trap cell, it deals damage.
// Each trap fires only once - after triggering it becomes inactive.
struct Trap
{
    Point position;
    int damage;
    bool triggered = false;
};

#endif