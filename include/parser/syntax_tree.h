#pragma once
#include <memory>
#include <vector>

class Token;

struct Program
{
    std::vector<std::unique_ptr<Statement>> statements;
};

struct Statement
{
    virtual ~Statement() {}
};

struct LiteralDefinition : public Statement
{
    bool canRedefine;
    std::unique_ptr<Token> literal;
};

struct Operation : public LiteralDefinition
{
    std::vector<std::unique_ptr<TurtleOperation>> turtleOperations;
};

struct Production : public LiteralDefinition
{
    std::vector<std::unique_ptr<Token>> literals;
};

struct Evaluation: public LiteralDefinition
{
    std::unique_ptr<Token> intNumber;
    std::vector<std::unique_ptr<Token>> literals;
};

struct LiteralExecution : public Statement
{
    std::vector<std::unique_ptr<Token>> literals;
};

struct TurtleStatementExecution : public Statement, public TurtleOperation
{

};

struct TurtleOperation
{
    std::unique_ptr<Token> type;
    std::unique_ptr<Token> arguments[3];
};
