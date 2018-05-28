#pragma once
#include <cstdint>
#include <string>
#include <SFML/Graphics.hpp>

namespace semantics_namespace
{

struct UtmostTurtleCoordinates // needed to initialize DrawingContext, calculated in CodeAnalyzer
{
    float maxX, maxY, minX, minY;
};

struct DrawingContext
{
    DrawingContext(const UtmostTurtleCoordinates &coord);
    void save(const std::string &filename);
    sf::RenderTexture target;

    const std::pair<float, float> middlePoint;
    static const sf::Color defaultColour;
};

struct TurtleState
{
    uint8_t pencolour[3];
    bool pendown;
    float position[2];
    float rotation;
    float pensize;
    float scale;

    TurtleState();
    void setPositionInTheMiddle(UtmostTurtleCoordinates &sd);
};

}
