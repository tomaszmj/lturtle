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
    : pendown(true), rotation(0.0f), pensize(1.0f), scale(1.0f)
{
    pencolour[0] = pencolour[1] = pencolour[2] = 0;
    position[0] = position[1] = 0;
}

void TurtleState::setPositionInTheMiddle(UtmostTurtleCoordinates &sd)
{
    position[0] = (sd.minX + sd.maxX)/2.0f;
    position[1] = (sd.minY + sd.maxY)/2.0f;
}
