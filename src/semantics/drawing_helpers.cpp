#include "drawing_helpers.h"
#include "exception.h"

using namespace semantics_namespace;

const sf::Color DrawingContext::defaultColour(255, 255, 255);

UtmostTurtleCoordinates::UtmostTurtleCoordinates(const std::pair<float, float> &starting_pos)
    : maxX(starting_pos.first), minX(starting_pos.first), maxY(starting_pos.second), minY(starting_pos.second)
{}

void UtmostTurtleCoordinates::update(const std::pair<float, float> &pos)
{
    if(pos.first < minX)
        minX = pos.first;
    if(pos.first > maxX)
        maxX = pos.first;
    if(pos.second < minY)
        minY = pos.second;
    if(pos.second > maxY)
        maxY = pos.second;
}

DrawingContext::DrawingContext(const UtmostTurtleCoordinates &coord)
    : middlePoint((coord.getMaxX() + coord.getMinX())/2.0f, (coord.getMaxY() + coord.getMinY())/2.0f)
{
    unsigned width = static_cast<unsigned>(coord.getMaxX() - coord.getMinX()) + 4; // +4 - 2-pixel margin
    unsigned height = static_cast<unsigned>(coord.getMaxY() - coord.getMinY()) + 4;
    target.create(width, height);
    target.clear(defaultColour);
}

void DrawingContext::save(const std::string &filename)
{
    if(!target.getTexture().copyToImage().saveToFile(filename))
        throw Exception("failed to save image in file " + filename);
}

TurtleState::TurtleState()
    : pencolour(0, 0, 0), pendown(true), position(0.0f, 0.0f), rotation(90.0f), pensize(1.0f), scale(1.0f)
{}
