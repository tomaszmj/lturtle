#include "variable.h"
#include "syntax_tree.h"
#include "turtle_operation.h"

using namespace semantics_namespace;

Variable::Variable()
{

}

bool Variable::hasProduction() const
{

}

bool Variable::hasEvaluation() const
{

}

bool Variable::hasOperations() const
{

}

const std::vector<std::reference_wrapper<Variable>> &Variable::getProduction() const
{

}

const std::vector<std::reference_wrapper<Variable>> &Variable::getEvaluation() const
{

}

const std::vector<std::unique_ptr<TurtleOperation> > &Variable::getOperations() const
{

}

VariableMap::VariableMap()
{

}

void VariableMap::define(parser_namespace::Definition &definition)
{

}

const Variable &VariableMap::get(lexer_namespace::Token::ValueString &token)
{

}
