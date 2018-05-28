#pragma once
#include <cstdint>
#include <string>
#include <SFML/Graphics.hpp>

namespace semantics_namespace
{

struct TurtleState
{
    sf::Color pencolour;
    bool pendown;
    std::pair<float, float> position;
    float rotation;
    float pensize;
    float scale;

    TurtleState();
};

class UtmostTurtleCoordinates // needed to initialize DrawingContext
{
public:
    UtmostTurtleCoordinates(const std::pair<float, float> &starting_pos);
    void update(const std::pair<float, float> &position); // changes min/max X/Y, used in turtle operations called by CodeAnalyzer
    void update(float pensize); // changes margin
    float getMaxX() const { return maxX; }
    float getMinX() const { return minX; }
    float getMaxY() const { return maxY; }
    float getMinY() const { return minY; }
    float getMargin() const { return margin; }

private:
    float maxX, minX, maxY, minY, margin;
};

class DrawingContext
{
public:
    DrawingContext(const UtmostTurtleCoordinates &coord);
    void save(const std::string &filename);
    void drawLine(const TurtleState &state, float length);
    std::pair<float, float> transfromTurtleCoordinatesToImageCoordinates(const std::pair<float, float> &point) const;

private:
    sf::RenderTexture target;
    const float xNegativeOffset, yPositiveOffset;
    static const sf::Color defaultColour;
};

}
