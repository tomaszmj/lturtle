#include "turtle_state.h"

semantics_namespace::TurtleState::TurtleState()
    : pendown(true), rotation(0.0f), pensize(1.0f), scale(1.0f)
{
    pencolour[0] = pencolour[1] = pencolour[2] = 0;
    position[0] = position[1] = 0;
}
