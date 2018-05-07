#pragma once
#include <memory>
#include <vector>

namespace lexer
{
class Token;
}

namespace parser
{

struct Statement;
struct LiteralString;
struct TurtleOperation;
struct TurtleOperationArguments;

struct Program
{
    std::vector<std::unique_ptr<Statement>> statements;

    std::string toString() const;
};

struct Statement
{
    enum Type
    {
        operation, production, evaluation, literal_execution, turtle_operation_execution
    };

    virtual Type getType() const = 0;
    virtual std::string toString() const = 0; // ugly, but simplifies testing
    virtual ~Statement() {}
};

struct Definition : public Statement
{
    bool canRedefine;
    std::unique_ptr<lexer::Token> literal;

    virtual std::string toString() const;
};

struct Operation : public Definition
{
    std::vector<std::unique_ptr<TurtleOperation>> turtleOperations;

    virtual Type getType() const { return operation; }
    virtual std::string toString() const;
};

struct Production : public Definition
{
    std::unique_ptr<LiteralString> literals;

    virtual Type getType() const { return production; }
    virtual std::string toString() const;
};

struct Evaluation: public Definition
{
    std::unique_ptr<lexer::Token> intNumber;
    std::unique_ptr<LiteralString> literals;

    virtual Type getType() const { return evaluation; }
    virtual std::string toString() const;
};

struct LiteralExecution : public Statement
{
    std::unique_ptr<LiteralString> literals;

    virtual Type getType() const { return literal_execution; }
    virtual std::string toString() const;
};

struct TurtleOperationExecution : public Statement
{
    std::unique_ptr<TurtleOperation> turtleOperation;

    virtual Type getType() const { return turtle_operation_execution; }
    virtual std::string toString() const;
};

struct LiteralString
{
    std::vector<std::unique_ptr<lexer::Token>> literals;

    std::string toString() const;
};

struct TurtleOperation
{
    enum Type
    {
        forward_operation, rotate_operation, penup_operation, pendown_operation,
        pencolour_operation, goto_operation, pensize_operation,
        scale_operation, pushstate_operation, popstate_operation
    } type;
    std::unique_ptr<TurtleOperationArguments> arguments;

    std::string toString() const;
};

struct TurtleOperationArguments
{
    std::vector<std::unique_ptr<lexer::Token>> numbers;

    std::string toString() const;
};

}
