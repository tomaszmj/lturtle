#pragma once
#include <cstdint>

namespace semantics
{

struct TurtleState
{
    uint8_t pencolour[3];
    bool pendown;
    float position[2];
    float rotation;
    float pensize;
    float scale;

    TurtleState();
};

}
