#include "turtle_operation.h"
#include "syntax_tree.h"
#include "drawing_helpers.h"
#include "exception.h"
#include "token.h"
#include <cmath>

using namespace semantics_namespace;

namespace
{
    void checkNumberOfArguments(const parser_namespace::TurtleOperation &operation, unsigned args_number, const std::string &name)
    {
        auto &numbers = operation.arguments->numbers;
        if(numbers.size() != args_number)
        {
            if(args_number == 1)
                throw SemanticsException(name + " operation expects exactly 1 argument, got " +
                                         std::to_string(numbers.size()), *numbers.back());
            else
                throw SemanticsException(name + " operation expects exactly " + std::to_string(args_number) +
                                         " argument, got " + std::to_string(numbers.size()), *numbers.back());
        }
    }
}

std::vector<TurtleState> TurtleOperation::stateStack;

std::unique_ptr<TurtleOperation> TurtleOperation::create(parser_namespace::TurtleOperation &operation)
{
    switch(operation.type)
    {
        case parser_namespace::TurtleOperation::forward_operation:
            return std::unique_ptr<TurtleOperation>(new TurtleOperationForward(operation));
        case parser_namespace::TurtleOperation::rotate_operation:
            return std::unique_ptr<TurtleOperation>(new TurtleOperationRotate(operation));
        case parser_namespace::TurtleOperation::penup_operation:
            checkNumberOfArguments(operation, 0, "penup");
            return std::unique_ptr<TurtleOperation>(new TurtleOperationPenup);
        case parser_namespace::TurtleOperation::pendown_operation:
            checkNumberOfArguments(operation, 0, "pendown");
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
            checkNumberOfArguments(operation, 0, "pushstate");
            return std::unique_ptr<TurtleOperation>(new TurtleOperationPushstate);
        case parser_namespace::TurtleOperation::popstate_operation:
            checkNumberOfArguments(operation, 0, "popstate");
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
    checkNumberOfArguments(operation, 1, "forward");
    auto &numbers = operation.arguments->numbers;
    arg = numbers[0]->getFloat();
    if(arg <= 0.0f)
        throw SemanticsException("forward operation argument must be positive, got " + std::to_string(arg), *numbers[0]);
}

TurtleOperationForward::TurtleOperationForward(const TurtleOperationForward &other)
    : arg(other.arg)
{}

std::unique_ptr<TurtleOperation> TurtleOperationForward::clone() const
{
    return std::unique_ptr<TurtleOperation>(new TurtleOperationForward(*this));
}

void TurtleOperationForward::applyAndUpdateUtmostCoordinates(TurtleState &state, UtmostTurtleCoordinates &coords)
{

}

void TurtleOperationForward::applyAndDraw(TurtleState &state, DrawingContext &context)
{

}

TurtleOperationRotate::TurtleOperationRotate(parser_namespace::TurtleOperation &operation)
{
    checkNumberOfArguments(operation, 1, "rotate");
    auto &numbers = operation.arguments->numbers;
    arg = numbers[0]->getFloat();
    if(std::fabs(arg) > 180.0f)
        throw SemanticsException("rotate operation argument must be in range [-180, 180], got " + std::to_string(arg), *numbers[0]);
}

TurtleOperationRotate::TurtleOperationRotate(const TurtleOperationRotate &other)
    : arg(other.arg)
{}

std::unique_ptr<TurtleOperation> TurtleOperationRotate::clone() const
{
    return std::unique_ptr<TurtleOperation>(new TurtleOperationRotate(*this));
}

void TurtleOperationRotate::applyAndUpdateUtmostCoordinates(TurtleState &state, UtmostTurtleCoordinates &coords)
{

}

void TurtleOperationRotate::applyAndDraw(TurtleState &state, DrawingContext &context)
{

}

std::unique_ptr<TurtleOperation> TurtleOperationPenup::clone() const
{
    return std::unique_ptr<TurtleOperation>(new TurtleOperationPenup(*this));
}

void TurtleOperationPenup::applyAndUpdateUtmostCoordinates(TurtleState &state, UtmostTurtleCoordinates &coords)
{

}

void TurtleOperationPenup::applyAndDraw(TurtleState &state, DrawingContext &context)
{

}

std::unique_ptr<TurtleOperation> TurtleOperationPendown::clone() const
{
    return std::unique_ptr<TurtleOperation>(new TurtleOperationPendown);
}

void TurtleOperationPendown::applyAndUpdateUtmostCoordinates(TurtleState &state, UtmostTurtleCoordinates &coords)
{

}

void TurtleOperationPendown::applyAndDraw(TurtleState &state, DrawingContext &context)
{

}

TurtleOperationPencolour::TurtleOperationPencolour(parser_namespace::TurtleOperation &operation)
{
    checkNumberOfArguments(operation, 3, "pencolour");
    auto &numbers = operation.arguments->numbers;
    for(int i = 0; i < 3; ++i)
    {
        const lexer_namespace::Token &t = *numbers[i];
        if(t.getSymbol() != lexer_namespace::Token::int_number)
            throw SemanticsException("pencolour operation arguments must be integers, not floats", t);
        int c = t.getInt();
        if(c < 0 || c > 255)
            throw SemanticsException("pencolour operation arguments must be integers in range [0, 255], got "
                                     + std::to_string(c), t);
        colour[i] = static_cast<uint8_t>(c);
    }
}

TurtleOperationPencolour::TurtleOperationPencolour(const TurtleOperationPencolour &other)
    : colour(other.colour)
{}

std::unique_ptr<TurtleOperation> TurtleOperationPencolour::clone() const
{
    return std::unique_ptr<TurtleOperation>(new TurtleOperationPencolour(*this));
}

void TurtleOperationPencolour::applyAndUpdateUtmostCoordinates(TurtleState &state, UtmostTurtleCoordinates &coords)
{

}

void TurtleOperationPencolour::applyAndDraw(TurtleState &state, DrawingContext &context)
{

}

TurtleOperationGoto::TurtleOperationGoto(parser_namespace::TurtleOperation &operation)
{
    checkNumberOfArguments(operation, 2, "goto");
    auto &numbers = operation.arguments->numbers;
    x = numbers[0]->getFloat();
    y = numbers[1]->getFloat();
}

TurtleOperationGoto::TurtleOperationGoto(const TurtleOperationGoto &other)
    : x(other.x), y(other.y)
{}

std::unique_ptr<TurtleOperation> TurtleOperationGoto::clone() const
{
    return std::unique_ptr<TurtleOperation>(new TurtleOperationGoto(*this));
}

void TurtleOperationGoto::applyAndUpdateUtmostCoordinates(TurtleState &state, UtmostTurtleCoordinates &coords)
{

}

void TurtleOperationGoto::applyAndDraw(TurtleState &state, DrawingContext &context)
{

}

TurtleOperationPensize::TurtleOperationPensize(parser_namespace::TurtleOperation &operation)
{
    checkNumberOfArguments(operation, 1, "pensize");
    auto &numbers = operation.arguments->numbers;
    arg = numbers[0]->getFloat();
    if(arg <= 0.0f)
        throw SemanticsException("pensize operation argument must be positive, got " + std::to_string(arg), *numbers[0]);
}

TurtleOperationPensize::TurtleOperationPensize(const TurtleOperationPensize &other)
    : arg(other.arg)
{}

std::unique_ptr<TurtleOperation> TurtleOperationPensize::clone() const
{
    return std::unique_ptr<TurtleOperation>(new TurtleOperationPensize(*this));
}

void TurtleOperationPensize::applyAndUpdateUtmostCoordinates(TurtleState &state, UtmostTurtleCoordinates &coords)
{

}

void TurtleOperationPensize::applyAndDraw(TurtleState &state, DrawingContext &context)
{

}

TurtleOperationScale::TurtleOperationScale(parser_namespace::TurtleOperation &operation)
{
    checkNumberOfArguments(operation, 1, "scale");
    auto &numbers = operation.arguments->numbers;
    arg = numbers[0]->getFloat();
    if(arg <= 0.0f)
        throw SemanticsException("scale operation argument must be positive, got " + std::to_string(arg), *numbers[0]);
}

TurtleOperationScale::TurtleOperationScale(const TurtleOperationScale &other)
    : arg(other.arg)
{}

std::unique_ptr<TurtleOperation> TurtleOperationScale::clone() const
{
    return std::unique_ptr<TurtleOperation>(new TurtleOperationScale(*this));
}

void TurtleOperationScale::applyAndUpdateUtmostCoordinates(TurtleState &state, UtmostTurtleCoordinates &coords)
{

}

void TurtleOperationScale::applyAndDraw(TurtleState &state, DrawingContext &context)
{

}

std::unique_ptr<TurtleOperation> TurtleOperationPushstate::clone() const
{
    return std::unique_ptr<TurtleOperation>(new TurtleOperationPushstate);
}

void TurtleOperationPushstate::applyAndUpdateUtmostCoordinates(TurtleState &state, UtmostTurtleCoordinates &coords)
{

}

void TurtleOperationPushstate::applyAndDraw(TurtleState &state, DrawingContext &context)
{

}

std::unique_ptr<TurtleOperation> TurtleOperationPopstate::clone() const
{
    return std::unique_ptr<TurtleOperation>(new TurtleOperationPopstate);
}

void TurtleOperationPopstate::applyAndUpdateUtmostCoordinates(TurtleState &state, UtmostTurtleCoordinates &coords)
{

}

void TurtleOperationPopstate::applyAndDraw(TurtleState &state, DrawingContext &context)
{

}
