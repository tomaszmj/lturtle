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
    void defineOperation(const parser_namespace::Operation &definition);
    void defineProduction(const parser_namespace::Production &definition);
    void defineEvaluation(const parser_namespace::Evaluation &definition);
    static void evaluationIteration(const std::vector<std::reference_wrapper<Variable>> &from,
                                    std::vector<std::reference_wrapper<Variable>> &to);
    const Variable *find(const std::string &variable_name) const; // returns nullptr if not found
    Variable *findNonconst(const std::string &variable_name); // returns nullptr if not found
    const Variable &findOrThrow(const lexer_namespace::Token &literal) const; // throws if not found
    Variable &findOrThrowNonconst(const lexer_namespace::Token &literal); // throws if not found
    Variable &insertOrFindAndRedefine(const parser_namespace::Definition &definition); // inserts if not found

private:
    std::unordered_map<std::string, Variable> map;
};

}
