#pragma once
#ifndef POINT_H
#define POINT_H

// Point represents a coordinate (x, y) on the game board.

struct Point
{
    int x;
    int y;

    bool operator==(const Point& other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Point& other) const
    {
        return !(*this == other);
    }
};

#endif