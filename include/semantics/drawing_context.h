#pragma once
#include <string>

namespace semantics_namespace
{

struct UtmostTurtleCoordinates // needed to initialize DrawingContext, calculated in CodeAnalyzer (see file interpreter.h)
{
    float maxX, maxY, minX, minY;
};

class DrawingContext
{
public:
    DrawingContext();
    void init(const UtmostTurtleCoordinates &coord);
};

}
