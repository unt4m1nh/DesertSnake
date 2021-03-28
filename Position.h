#ifndef POSITION_H
#define POSITION_H

#include<stdexcept>

enum direction
{
    up = 2;
    down = 3;
    left = 0;
    right = 1;
};

struct Position
{
    int x;
    int y;
    int x0;
    int y0;
};

#endif // POSITION_H
