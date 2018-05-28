#include "drawing_helpers.h"
#include "exception.h"
#ifdef DEBUG
#include <iostream>
#endif

using namespace semantics_namespace;

TurtleState::TurtleState()
    : pencolour(0, 0, 0), pendown(true), position(0.0f, 0.0f), rotation(90.0f), pensize(1.0f), scale(1.0f)
{}

UtmostTurtleCoordinates::UtmostTurtleCoordinates(const std::pair<float, float> &starting_pos)
    : maxX(starting_pos.first), minX(starting_pos.first), maxY(starting_pos.second), minY(starting_pos.second), margin(1.0)
{}

void UtmostTurtleCoordinates::update(const std::pair<float, float> &position)
{
    if(position.first < minX)
        minX = position.first;
    if(position.first > maxX)
        maxX = position.first;
    if(position.second < minY)
        minY = position.second;
    if(position.second > maxY)
        maxY = position.second;
}

void UtmostTurtleCoordinates::update(float pensize)
{
    if(pensize > margin)
        margin = pensize;
}

const sf::Color DrawingContext::defaultColour(255, 255, 255);

DrawingContext::DrawingContext(const UtmostTurtleCoordinates &coord)
    : xNegativeOffset(coord.getMinX() - coord.getMargin()), yPositiveOffset(coord.getMaxY() + coord.getMargin())
{
    unsigned width = static_cast<unsigned>(coord.getMaxX() - coord.getMinX() + 2*coord.getMargin());
    unsigned height = static_cast<unsigned>(coord.getMaxY() - coord.getMinY() + 2*coord.getMargin());
    target.create(width, height);
    target.clear(defaultColour);
    target.setSmooth(true);
}

void DrawingContext::save(const std::string &filename)
{
    target.getTexture().copyToImage().saveToFile(filename); // SFML "witout asking" itself prints error message
}

void DrawingContext::drawLine(const TurtleState &state, float length)
{
    if(!state.pendown)
        return;
    sf::RectangleShape line(sf::Vector2f(state.scale * length, state.scale * state.pensize));
    line.setRotation(-state.rotation); // setRotation(number of DEGREES), clockwise (state.rotation is counter-clockwise)
    line.setFillColor(state.pencolour);
    std::pair<float, float> point = transfromTurtleCoordinatesToImageCoordinates(state.position);
    line.setPosition(point.first, point.second);
    target.draw(line);
}

std::pair<float, float> DrawingContext::transfromTurtleCoordinatesToImageCoordinates(const std::pair<float, float> &point) const
{
#ifdef DEBUG
    std::cerr << "transfrom coordinates (" << point.first << ", " << point.second << ") -> (" << point.first - xNegativeOffset << ", " << yPositiveOffset - point.second << ")\n";
#endif
    return std::pair<float, float>(point.first - xNegativeOffset, yPositiveOffset - point.second);
}
