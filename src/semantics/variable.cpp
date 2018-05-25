#include "variable.h"
#include "syntax_tree.h"
#include "turtle_operation.h"
#include "exception.h"

using namespace semantics_namespace;

bool Variable::hasProduction() const
{
    return hasProductionFlag;
}

bool Variable::hasEvaluation() const
{
    return hasEvaluationFlag;
}

bool Variable::hasOperations() const
{
    return !hasEvaluationFlag;
}

const std::vector<std::reference_wrapper<Variable>> &Variable::getProduction() const
{
    return production;
}

const std::vector<std::reference_wrapper<Variable>> &Variable::getEvaluation() const
{
    return evaluation;
}

const std::vector<std::unique_ptr<TurtleOperation>> &Variable::getOperations() const
{
    return operations;
}

Variable::Variable()
    : hasProductionFlag(false), hasEvaluationFlag(false)
{}

VariableMap::VariableMap()
{}

void VariableMap::defineOperation(const parser_namespace::Operation &definition)
{
    Variable &var = insertOrFindAndRedefine(definition);
    var.operations.reserve(definition.turtleOperations.size());
    var.operations.clear();
    for(const std::unique_ptr<parser_namespace::TurtleOperation> &operation : definition.turtleOperations)
        var.operations.push_back(TurtleOperation::create(*operation));
}

void VariableMap::defineProduction(const parser_namespace::Production &definition)
{
    Variable &var = findOrThrow(*definition.literal);
    if(var.hasProduction() && !definition.canRedefine)
        throw SemanticsException("attempt to redefine production of variable " + definition.literal->getLiteral() +
                                 " without 'redefine'", *definition.literal);
    var.hasProductionFlag = true;
    var.production.reserve(definition.literals->literalsVector.size());
    var.production.clear();
    for(const std::unique_ptr<lexer_namespace::Token> &literal : definition.literals->literalsVector)
        var.production.push_back(findOrThrow(*literal));
}

void VariableMap::defineEvaluation(const parser_namespace::Evaluation &definition)
{
    Variable &var = insertOrFindAndRedefine(definition);
    var.hasEvaluationFlag = true;
    int iterations_left = definition.intNumber->getInt();
    if(iterations_left <= 0)
        throw SemanticsException("excepted positive integer as evaluation argument, got " + std::to_string(iterations_left), *definition.literal);
    std::array<std::vector<std::reference_wrapper<Variable>>, 2> vectors; // 2-element circular buffer
    vectors[0].reserve(definition.literals->literalsVector.size());
    for(const std::unique_ptr<lexer_namespace::Token> &literal : definition.literals->literalsVector)
        vectors[0].push_back(findOrThrow(*literal));
    int from_index = 0, to_index = 1;
    while(--iterations_left >= 0)
    {
        evaluationIteration(vectors[from_index], vectors[to_index]);
        std::swap(from_index, to_index);
    }
    var.evaluation.clear();
    var.evaluation.insert(var.evaluation.end(), vectors[from_index].begin(), vectors[from_index].end());
}

void VariableMap::evaluationIteration(const std::vector<std::reference_wrapper<Variable>> &from,
                                      std::vector<std::reference_wrapper<Variable>> &to)
{
    to.clear();
    for(const auto &variable : from)
    {
        if(!variable.get().hasProduction())
            to.push_back(variable);
        else
            to.insert(to.end(), variable.get().getProduction().begin(), variable.get().getProduction().end());
    }
}

const Variable *VariableMap::find(const std::string &variable_name) const
{
    auto it = map.find(variable_name);
    if(it == map.end())
        return nullptr;
    return &(it->second);
}

Variable *VariableMap::findNonconst(const std::string &variable_name)
{
    return const_cast<Variable*>(find(variable_name));
}

Variable &VariableMap::findOrThrow(const lexer_namespace::Token &literal)
{
    Variable *var = findNonconst(literal.getLiteral());
    if(var == nullptr)
        throw SemanticsException("access to undefined variable " + literal.getLiteral(), literal);
    return *var;
}

Variable &VariableMap::insertOrFindAndRedefine(const parser_namespace::Definition &definition)
{
    const auto &literal = definition.literal;
    auto it = map.find(literal->getLiteral());
    if(it != map.end())
    {
        if(definition.canRedefine)
            return it->second;
        throw SemanticsException("attempt to redefine variable " + literal->getLiteral() + " without 'redefine'", *definition.literal);
    }
    it = map.insert(it, std::pair<std::string, Variable>(literal->getLiteral(), Variable()));
    return it->second;
}
