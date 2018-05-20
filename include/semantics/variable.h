#pragma once
#include "token.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

namespace parser_namespace
{
class Definition;
class LiteralString;
class Operation;
}

namespace semantics_namespace
{

class TurtleOperation;

class Variable
{
public:
    friend class VariableMap;

    bool hasProduction() const;
    bool hasEvaluation() const;
    bool hasOperations() const;
    const std::vector<std::reference_wrapper<Variable>> &getProduction() const;
    const std::vector<std::reference_wrapper<Variable>> &getEvaluation() const;
    const std::vector<std::unique_ptr<TurtleOperation>> &getOperations() const;

private:
    bool hasProductionFlag;
    bool hasEvaluationFlag;
    // there is no hasOperationFlag, because Variable either has operations or evaluation
    std::vector<std::reference_wrapper<Variable>> production;
    std::vector<std::reference_wrapper<Variable>> evaluation;
    std::vector<std::unique_ptr<TurtleOperation>> operations;

    Variable(); // Variable can be constructed only with VariableMap::define()
};

class VariableMap
{
public:
    VariableMap();
    void define(parser_namespace::Definition &definition);
    const Variable &get(const std::string &variable_name);

private:
    std::unordered_map<std::string, Variable> map;
};

}
