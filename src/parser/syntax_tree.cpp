#include "syntax_tree.h"
#include "token.h"

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
    retval += "};";
    return retval;
}

std::string Production::toString() const
{
    return Definition::toString() + " -> " + literals->toString() + ";\n";
}

std::string Evaluation::toString() const
{
    return Definition::toString() + " = evaluate( " + std::to_string(intNumber->getInt()) +
            ", " + literals->toString() + " );\n";
}

std::string LiteralExecution::toString() const
{
    return "execute( " + literals->toString() + " );\n";
}

std::string TurtleOperationExecution::toString() const
{
    return turtleOperation->toString() + ";\n";
}

std::string LiteralString::toString() const
{
    std::string retval = literals[0]->getLiteral();
    for(size_t i = 1; i < literals.size(); ++i)
        retval += " + " + literals[i]->getLiteral();
    return retval;
}

std::string TurtleOperation::toString() const
{
    switch(type) // will be changed - arguments will also be added to the string
    {
        case TurtleOperation::forward_operation:
            return "forward";
        case TurtleOperation::rotate_operation:
            return "rotate";
        case TurtleOperation::penup_operation:
            return "penup";
        case TurtleOperation::pendown_operation:
            return "pendown";
        case TurtleOperation::pencolour_operation:
            return "pencolour";
        case TurtleOperation::goto_operation:
            return "goto";
        case TurtleOperation::pensize_operation:
            return "pensize";
        case TurtleOperation::scale_operation:
            return "scale";
        case TurtleOperation::pushstate_operation:
            return "pushstate";
        case TurtleOperation::popstate_operation:
            return "popstate";
    }
    return ""; // impossible (all enum cases exhausted) - suppress compiler warning
}
