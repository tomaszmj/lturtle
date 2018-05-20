#include "syntax_tree.h"
#include "token.h"

using namespace parser_namespace;

std::string Program::toString() const
{
    std::string retval;
    for(const auto &statement : statements)
        retval += statement->toString() + ";\n";
    return retval;
}

std::string Definition::toString() const
{
    if(canRedefine)
        return "redefine " + literal->getLiteral();
    return literal->getLiteral();
}

std::string Operation::toString() const
{
    std::string retval = Definition::toString() + " = { ";
    for(const auto &to : turtleOperations)
        retval += to->toString() + "; ";
    retval += "}";
    return retval;
}

std::string Production::toString() const
{
    return Definition::toString() + " -> " + literals->toString();
}

std::string Evaluation::toString() const
{
    return Definition::toString() + " = evaluate(" + std::to_string(intNumber->getInt()) +
            ", " + literals->toString() + ")";
}

std::string LiteralExecution::toString() const
{
    return "execute(" + literals->toString() + ")";
}

std::string TurtleOperationExecution::toString() const
{
    return turtleOperation->toString();
}

std::string LiteralString::toString() const
{
    std::string retval = literalsVector[0]->toString();
    for(size_t i = 1; i < literalsVector.size(); ++i)
        retval += " + " + literalsVector[i]->toString();
    return retval;
}

std::string TurtleOperation::toString() const
{
    switch(type) // will be changed - arguments will also be added to the string
    {
        case TurtleOperation::forward_operation:
            return "forward(" + arguments->toString() + ")";
        case TurtleOperation::rotate_operation:
            return "rotate(" + arguments->toString() + ")";
        case TurtleOperation::penup_operation:
            return "penup(" + arguments->toString() + ")";
        case TurtleOperation::pendown_operation:
            return "pendown(" + arguments->toString() + ")";
        case TurtleOperation::pencolour_operation:
            return "pencolour(" + arguments->toString() + ")";
        case TurtleOperation::goto_operation:
            return "goto(" + arguments->toString() + ")";
        case TurtleOperation::pensize_operation:
            return "pensize(" + arguments->toString() + ")";
        case TurtleOperation::scale_operation:
            return "scale(" + arguments->toString() + ")";
        case TurtleOperation::pushstate_operation:
            return "pushstate(" + arguments->toString() + ")";
        case TurtleOperation::popstate_operation:
            return "popstate(" + arguments->toString() + ")";
    }
    return ""; // impossible (all enum cases exhausted) - suppress compiler warning
}

std::string TurtleOperationArguments::toString() const
{
    if(numbers.empty())
        return "";
    std::string retval = numbers[0]->toString();
    for(size_t i = 1; i < numbers.size(); ++i)
        retval += ", " + numbers[i]->toString();
    return retval;
}
