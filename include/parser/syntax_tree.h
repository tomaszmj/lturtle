#pragma once
#include <memory>
#include <vector>

class Token;
struct Statement;
struct LiteralString;
struct TurtleOperation;

struct Program
{
    std::vector<std::unique_ptr<Statement>> statements;
};

struct Statement
{
    virtual ~Statement() {}
};

struct Definition : public Statement
{
    bool canRedefine;
    std::unique_ptr<Token> literal;
};

struct Operation : public Definition
{
    std::vector<std::unique_ptr<TurtleOperation>> turtleOperations;
};

struct Production : public Definition
{
    std::unique_ptr<LiteralString> literals;
};

struct Evaluation: public Definition
{
    std::unique_ptr<Token> intNumber;
    std::unique_ptr<LiteralString> literals;
};

struct LiteralExecution : public Statement
{
    std::unique_ptr<LiteralString> literals;
};

struct TurtleOperationExecution : public Statement
{
    std::unique_ptr<TurtleOperation> operation;
};

struct LiteralString
{
    std::vector<std::unique_ptr<Token>> literals;
};

struct TurtleOperation
{
    enum Type
    {
        forward_operation, rotate_operation, penup_operation, pendown_operation,
        pencolour_operation, goto_operation, pensize_operation,
        scale_operation, pushstate_operation, popstate_operation
    } type;
    std::unique_ptr<Token> arguments[3];
};
