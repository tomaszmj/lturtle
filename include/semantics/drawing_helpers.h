#pragma once
#include <cstdint>
#include <string>
#include <SFML/Graphics.hpp>

namespace semantics_namespace
{

class UtmostTurtleCoordinates // needed to initialize DrawingContext
{
public:
    UtmostTurtleCoordinates(const std::pair<float, float> &starting_pos);
    void update(const std::pair<float, float> &pos); // used in turtle operations called by CodeAnalyzer
    float getMaxX() const { return maxX; }
    float getMinX() const { return minX; }
    float getMaxY() const { return maxY; }
    float getMinY() const { return minY; }

private:
    float maxX, minX, maxY, minY;
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
    sf::Color pencolour;
    bool pendown;
    std::pair<float, float> position;
    float rotation;
    float pensize;
    float scale;

    TurtleState();
};

}
