#pragma once
#include "token.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

namespace parser
{
class Definition;
class LiteralString;
class Operation;
}

namespace semantics
{

class TurtleOperation;

class Variable
{
public:
    friend class VariableMap;

    bool hasProduction() const;
    bool hasEvaluation() const;
    bool hasOperations() const;
    const std::vector<std::reference_wrapper<Variable>> getProduction() const;
    const std::vector<std::reference_wrapper<Variable>> getEvaluation() const;
    const std::vector<std::reference_wrapper<TurtleOperation>> getOperations() const;

private:
    int state;
    std::vector<std::reference_wrapper<Variable>> production;
    std::vector<std::reference_wrapper<Variable>> evaluation;
    std::vector<std::reference_wrapper<TurtleOperation>> operations;

    Variable(); // Variable can be constructed only with VariableMap::define()
};

class VariableMap
{
public:
    VariableMap();
    void define(parser::Definition &definition);
    const Variable& get(lexer::Token::ValueString &token);

private:
    std::unordered_map<std::string, Variable> map;
};

}
