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

void VariableMap::defineOperation(parser_namespace::Operation &definition)
{
    Variable &var = findOrInsert(definition);
    var.operations.reserve(definition.turtleOperations.size());
    var.operations.clear();
    for(const std::unique_ptr<parser_namespace::TurtleOperation> &operation : definition.turtleOperations)
        var.operations.push_back(TurtleOperation::create(*operation));
}

void VariableMap::defineProduction(parser_namespace::Production &definition)
{
    Variable &var = findOrThrow(definition);
    var.hasProductionFlag = true;
    var.production.reserve(definition.literals->literalsVector.size());
    var.production.clear();
    for(const std::unique_ptr<lexer_namespace::Token> &literal : definition.literals->literalsVector)
        var.production.emplace_back(findOrThrow(literal));
}

void VariableMap::defineEvaluation(parser_namespace::Evaluation &definition)
{
    Variable &var = findOrInsert(definition);
    var.hasEvaluationFlag = true;
    var.evaluation.reserve(definition.literals->literalsVector.size());
    var.evaluation.clear();
    for(const std::unique_ptr<lexer_namespace::Token> &literal : definition.literals->literalsVector)
        var.evaluation.emplace_back(findOrThrow(literal));
}

const Variable *VariableMap::find(const std::string &variable_name)
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

Variable &VariableMap::findOrThrow(const std::unique_ptr<lexer_namespace::Token> &literal)
{
    Variable *var = findNonconst(literal->getLiteral());
    if(var == nullptr)
        throw SemanticsException("access to undefined variable " + literal->getLiteral() +
            "\n(from " + literal->getPositionBegin().toString() + " to " + literal->getPositionEnd().toString() + ")");
    return *var;
}

Variable &VariableMap::findOrInsert(parser_namespace::Definition &definition)
{
    const auto &literal = definition.literal;
    auto it = map.find(literal->getLiteral());
    if(it != map.end())
    {
        if(definition.canRedefine)
            return it->second;
        throw SemanticsException("attempt to redefine variable " + literal->getLiteral() + " without 'redefine'"
            "' (from " + literal->getPositionBegin().toString() + " to " + literal->getPositionEnd().toString() + ")");
    }
    it = map.insert(it, std::pair<std::string, Variable>(literal->getLiteral(), Variable()));
    return it->second;
}
