#include "variable.h"
#include "syntax_tree.h"

using namespace semantics;

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

const std::vector<std::reference_wrapper<Variable>> Variable::getProduction() const
{

}

const std::vector<std::reference_wrapper<Variable>> Variable::getEvaluation() const
{

}

const std::vector<std::reference_wrapper<TurtleOperation>> Variable::getOperations() const
{

}

VariableMap::VariableMap()
{

}

void VariableMap::define(parser::Definition &definition)
{

}

const Variable &VariableMap::get(lexer::Token::ValueString &token)
{

}
