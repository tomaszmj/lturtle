#include "turtle_state.h"
#include "drawing_context.h"

using namespace semantics_namespace;

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
