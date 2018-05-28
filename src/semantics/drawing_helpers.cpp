#include "drawing_helpers.h"
#include "exception.h"

using namespace semantics_namespace;

TurtleState::TurtleState()
    : pencolour(0, 0, 0), pendown(true), position(0.0f, 0.0f), rotation(90.0f), pensize(1.0f), scale(1.0f)
{}

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

const sf::Color DrawingContext::defaultColour(255, 255, 255);

DrawingContext::DrawingContext(const UtmostTurtleCoordinates &coord)
    : middlePoint((coord.getMaxX() + coord.getMinX())/2.0f, (coord.getMaxY() + coord.getMinY())/2.0f)
{
    unsigned width = static_cast<unsigned>(coord.getMaxX() - coord.getMinX()) + 4; // +4 - 2-pixel margin
    unsigned height = static_cast<unsigned>(coord.getMaxY() - coord.getMinY()) + 4;
    target.create(width, height);
    target.clear(defaultColour);
    target.setSmooth(true);
}

void DrawingContext::save(const std::string &filename)
{
    if(!target.getTexture().copyToImage().saveToFile(filename))
        throw Exception("failed to save image in file " + filename);
}

void DrawingContext::drawLine(const TurtleState &state, float length)
{
    if(!state.pendown)
        return;
    sf::RectangleShape line(sf::Vector2f(state.scale * length, state.scale * state.pensize));
    line.setRotation(state.rotation);
    line.setFillColor(state.pencolour);
    line.setPosition(state.position.first + middlePoint.first, state.position.second + middlePoint.second);
    target.draw(line);
}
