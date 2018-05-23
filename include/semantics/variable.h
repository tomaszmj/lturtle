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
class Production;
class Evaluation;
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

    Variable(); // Variable can be constructed only with VariableMap::define...()
};

class VariableMap
{
public:
    VariableMap();
    void defineOperation(parser_namespace::Operation &definition);
    void defineProduction(parser_namespace::Production &definition);
    void defineEvaluation(parser_namespace::Evaluation &definition);
    const Variable *find(const std::string &variable_name); // returns nullptr if not found

private:
    Variable *findNonconst(const std::string &variable_name); // returns nullptr if not found
    Variable &findOrThrow(const std::unique_ptr<lexer_namespace::Token> &literal); // throws if not found
    Variable &findOrInsert(parser_namespace::Definition &definition); // inserts if not found
    std::unordered_map<std::string, Variable> map;
};

}
