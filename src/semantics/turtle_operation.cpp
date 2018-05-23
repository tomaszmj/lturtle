#include "turtle_operation.h"
#include "syntax_tree.h"
#include "turtle_state.h"
#include "drawing_context.h"

using namespace semantics_namespace;

std::unique_ptr<TurtleOperation> TurtleOperation::create(parser_namespace::TurtleOperation &operation)
{
    switch(operation.type)
    {
        case parser_namespace::TurtleOperation::forward_operation:
            return std::unique_ptr<TurtleOperation>(new TurtleOperationForward(operation));
        case parser_namespace::TurtleOperation::rotate_operation:
            return std::unique_ptr<TurtleOperation>(new TurtleOperationRotate(operation));
        case parser_namespace::TurtleOperation::penup_operation:
            return std::unique_ptr<TurtleOperation>(new TurtleOperationPenup);
        case parser_namespace::TurtleOperation::pendown_operation:
            return std::unique_ptr<TurtleOperation>(new TurtleOperationPendown);
        case parser_namespace::TurtleOperation::pencolour_operation:
            return std::unique_ptr<TurtleOperation>(new TurtleOperationPencolour(operation));
        case parser_namespace::TurtleOperation::goto_operation:
            return std::unique_ptr<TurtleOperation>(new TurtleOperationGoto(operation));
        case parser_namespace::TurtleOperation::pensize_operation:
            return std::unique_ptr<TurtleOperation>(new TurtleOperationPensize(operation));
        case parser_namespace::TurtleOperation::scale_operation:
            return std::unique_ptr<TurtleOperation>(new TurtleOperationScale(operation));
        case parser_namespace::TurtleOperation::pushstate_operation:
            return std::unique_ptr<TurtleOperation>(new TurtleOperationPushstate);
        case parser_namespace::TurtleOperation::popstate_operation:
            return std::unique_ptr<TurtleOperation>(new TurtleOperationPopstate);
    }
    return std::unique_ptr<TurtleOperation>(nullptr); // suppress compiler warning (impossible - all swich cases exhausted)
}

void TurtleOperation::resetStateStack()
{
    stateStack.clear();
}

TurtleOperationForward::TurtleOperationForward(parser_namespace::TurtleOperation &operation)
{

}

TurtleOperationForward::TurtleOperationForward(const TurtleOperationForward &other)
    : arg(other.arg)
{}

std::unique_ptr<TurtleOperation> TurtleOperationForward::clone() const
{
    return std::unique_ptr<TurtleOperation>(new TurtleOperationForward(*this));
}

void TurtleOperationForward::apply(TurtleState &state)
{

}

void TurtleOperationForward::applyAndDraw(TurtleState &state, DrawingContext &context)
{

}

TurtleOperationRotate::TurtleOperationRotate(parser_namespace::TurtleOperation &operation)
{

}

TurtleOperationRotate::TurtleOperationRotate(const TurtleOperationRotate &other)
    : arg(other.arg)
{}

std::unique_ptr<TurtleOperation> TurtleOperationRotate::clone() const
{
    return std::unique_ptr<TurtleOperation>(new TurtleOperationRotate(*this));
}

void TurtleOperationRotate::apply(TurtleState &state)
{

}

void TurtleOperationRotate::applyAndDraw(TurtleState &state, DrawingContext &context)
{

}

std::unique_ptr<TurtleOperation> TurtleOperationPenup::clone() const
{
    return std::unique_ptr<TurtleOperation>(new TurtleOperationPenup(*this));
}

void TurtleOperationPenup::apply(TurtleState &state)
{

}

void TurtleOperationPenup::applyAndDraw(TurtleState &state, DrawingContext &context)
{

}

std::unique_ptr<TurtleOperation> TurtleOperationPendown::clone() const
{
    return std::unique_ptr<TurtleOperation>(new TurtleOperationPendown);
}

void TurtleOperationPendown::apply(TurtleState &state)
{

}

void TurtleOperationPendown::applyAndDraw(TurtleState &state, DrawingContext &context)
{

}

TurtleOperationPencolour::TurtleOperationPencolour(parser_namespace::TurtleOperation &operation)
{

}

TurtleOperationPencolour::TurtleOperationPencolour(const TurtleOperationPencolour &other)
    : r(other.r), g(other.g), b(other.b)
{}

std::unique_ptr<TurtleOperation> TurtleOperationPencolour::clone() const
{
    return std::unique_ptr<TurtleOperation>(new TurtleOperationPencolour(*this));
}

void TurtleOperationPencolour::apply(TurtleState &state)
{

}

void TurtleOperationPencolour::applyAndDraw(TurtleState &state, DrawingContext &context)
{

}

TurtleOperationGoto::TurtleOperationGoto(parser_namespace::TurtleOperation &operation)
{

}

TurtleOperationGoto::TurtleOperationGoto(const TurtleOperationGoto &other)
    : x(other.x), y(other.y)
{}

std::unique_ptr<TurtleOperation> TurtleOperationGoto::clone() const
{
    return std::unique_ptr<TurtleOperation>(new TurtleOperationGoto(*this));
}

void TurtleOperationGoto::apply(TurtleState &state)
{

}

void TurtleOperationGoto::applyAndDraw(TurtleState &state, DrawingContext &context)
{

}

TurtleOperationPensize::TurtleOperationPensize(parser_namespace::TurtleOperation &operation)
{

}

TurtleOperationPensize::TurtleOperationPensize(const TurtleOperationPensize &other)
    : arg(other.arg)
{}

std::unique_ptr<TurtleOperation> TurtleOperationPensize::clone() const
{
    return std::unique_ptr<TurtleOperation>(new TurtleOperationPensize(*this));
}

void TurtleOperationPensize::apply(TurtleState &state)
{

}

void TurtleOperationPensize::applyAndDraw(TurtleState &state, DrawingContext &context)
{

}

TurtleOperationScale::TurtleOperationScale(parser_namespace::TurtleOperation &operation)
{

}

TurtleOperationScale::TurtleOperationScale(const TurtleOperationScale &other)
    : arg(other.arg)
{}

std::unique_ptr<TurtleOperation> TurtleOperationScale::clone() const
{
    return std::unique_ptr<TurtleOperation>(new TurtleOperationScale(*this));
}

void TurtleOperationScale::apply(TurtleState &state)
{

}

void TurtleOperationScale::applyAndDraw(TurtleState &state, DrawingContext &context)
{

}

std::unique_ptr<TurtleOperation> TurtleOperationPushstate::clone() const
{
    return std::unique_ptr<TurtleOperation>(new TurtleOperationPushstate);
}

void TurtleOperationPushstate::apply(TurtleState &state)
{

}

void TurtleOperationPushstate::applyAndDraw(TurtleState &state, DrawingContext &context)
{

}

std::unique_ptr<TurtleOperation> TurtleOperationPopstate::clone() const
{
    return std::unique_ptr<TurtleOperation>(new TurtleOperationPopstate);
}

void TurtleOperationPopstate::apply(TurtleState &state)
{

}

void TurtleOperationPopstate::applyAndDraw(TurtleState &state, DrawingContext &context)
{

}
