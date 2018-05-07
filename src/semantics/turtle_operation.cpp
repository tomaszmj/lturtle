#include "turtle_operation.h"
#include "syntax_tree.h"
#include "turtle_state.h"
#include "drawing_context.h"

using namespace semantics;

std::unique_ptr<TurtleOperation> TurtleOperation::createOperation(parser::TurtleOperation &operation)
{

}

TurtleOperationForward::TurtleOperationForward(parser::TurtleOperation &operation)
{

}

void TurtleOperationForward::apply(TurtleState &state)
{

}

void TurtleOperationForward::applyAndDraw(TurtleState &state, DrawingContext &context)
{

}

TurtleOperationRotate::TurtleOperationRotate(parser::TurtleOperation &operation)
{

}

void TurtleOperationRotate::apply(TurtleState &state)
{

}

void TurtleOperationRotate::applyAndDraw(TurtleState &state, DrawingContext &context)
{

}

TurtleOperationPenup::TurtleOperationPenup(parser::TurtleOperation &operation)
{

}

void TurtleOperationPenup::apply(TurtleState &state)
{

}

void TurtleOperationPenup::applyAndDraw(TurtleState &state, DrawingContext &context)
{

}

TurtleOperationPendown::TurtleOperationPendown(parser::TurtleOperation &operation)
{

}

void TurtleOperationPendown::apply(TurtleState &state)
{

}

void TurtleOperationPendown::applyAndDraw(TurtleState &state, DrawingContext &context)
{

}

TurtleOperationPencolour::TurtleOperationPencolour(parser::TurtleOperation &operation)
{

}

void TurtleOperationPencolour::apply(TurtleState &state)
{

}

void TurtleOperationPencolour::applyAndDraw(TurtleState &state, DrawingContext &context)
{

}

TurtleOperationGoto::TurtleOperationGoto(parser::TurtleOperation &operation)
{

}

void TurtleOperationGoto::apply(TurtleState &state)
{

}

void TurtleOperationGoto::applyAndDraw(TurtleState &state, DrawingContext &context)
{

}

TurtleOperationPensize::TurtleOperationPensize(parser::TurtleOperation &operation)
{

}

void TurtleOperationPensize::apply(TurtleState &state)
{

}

void TurtleOperationPensize::applyAndDraw(TurtleState &state, DrawingContext &context)
{

}

TurtleOperationScale::TurtleOperationScale(parser::TurtleOperation &operation)
{

}

void TurtleOperationScale::apply(TurtleState &state)
{

}

void TurtleOperationScale::applyAndDraw(TurtleState &state, DrawingContext &context)
{

}

TurtleOperationPushstate::TurtleOperationPushstate(parser::TurtleOperation &operation)
{

}

void TurtleOperationPushstate::apply(TurtleState &state)
{

}

void TurtleOperationPushstate::applyAndDraw(TurtleState &state, DrawingContext &context)
{

}

TurtleOperationPopstate::TurtleOperationPopstate(parser::TurtleOperation &operation)
{

}

void TurtleOperationPopstate::apply(TurtleState &state)
{

}

void TurtleOperationPopstate::applyAndDraw(TurtleState &state, DrawingContext &context)
{

}
