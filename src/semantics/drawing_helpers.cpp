#include "drawing_helpers.h"
#include "exception.h"

using namespace semantics_namespace;

const sf::Color DrawingContext::defaultColour(255, 255, 255);

DrawingContext::DrawingContext(const UtmostTurtleCoordinates &coord)
    : middlePoint((coord.maxX + coord.minX)/2.0f, (coord.maxY + coord.minY)/2.0f)
{
    unsigned width = static_cast<unsigned>(coord.maxX - coord.minX) + 4; // +4 - 2-pixel margin
    unsigned height = static_cast<unsigned>(coord.maxY - coord.minY) + 4;
    target.create(width, height);
    target.clear(defaultColour);
}

void DrawingContext::save(const std::string &filename)
{
    if(!target.getTexture().copyToImage().saveToFile(filename))
        throw Exception("failed to save image in file " + filename);
}

TurtleState::TurtleState()
    : pencolour(0, 0, 0), pendown(true), position(0.0f, 0.0f), rotation(0.0f), pensize(1.0f), scale(1.0f)
{}
