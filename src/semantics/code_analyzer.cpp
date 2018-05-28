#include "code_analyzer.h"
#include "exception.h"

using namespace semantics_namespace;

CodeAnalyzer::CodeAnalyzer(std::istream &input)
    : source(input), lexer(source), parser(lexer)
{
    std::unique_ptr<parser_namespace::Statement> statement;
    while((statement = parser.parseStatement()) != nullptr)
    {
        switch(statement->getType())
        {
            case parser_namespace::Statement::operation:
                variableMap.defineOperation(*dynamic_cast<parser_namespace::Operation*>(statement.get()));
                break;
            case parser_namespace::Statement::production:
                variableMap.defineProduction(*dynamic_cast<parser_namespace::Production*>(statement.get()));
                break;
            case parser_namespace::Statement::evaluation:
                variableMap.defineEvaluation(*dynamic_cast<parser_namespace::Evaluation*>(statement.get()));
                break;
            case parser_namespace::Statement::literal_execution:
                interpretLiteralExecution(dynamic_cast<parser_namespace::LiteralExecution*>(statement.get()));
                break;
            case parser_namespace::Statement::turtle_operation_execution:
                interpretTurtleOperationExecution(dynamic_cast<parser_namespace::TurtleOperationExecution*>(statement.get()));
                break;
        }
    }
}

std::vector<std::unique_ptr<TurtleOperation> > &&CodeAnalyzer::moveRawTurtleOperations()
{
    return std::move(rawTurtleOperations);
}

const UtmostTurtleCoordinates &CodeAnalyzer::getUtmostCoordinates() const
{
    return utmostCoordinates;
}

const VariableMap &CodeAnalyzer::getVariableMap() const
{
    return variableMap;
}

void CodeAnalyzer::interpretLiteralExecution(const parser_namespace::LiteralExecution *statement)
{
    for(const std::unique_ptr<lexer_namespace::Token> &literal : statement->literals->literalsVector)
    {
        const Variable &variable = variableMap.findOrThrow(*literal);
        interpretVariableExecution(variable);
    }
}

void CodeAnalyzer::interpretVariableExecution(const Variable &variable)
{
    if(variable.hasOperations())
    {
        for(const std::unique_ptr<TurtleOperation> &operation : variable.getOperations())
        {
            operation->applyAndUpdateUtmostCoordinates(turtleState, utmostCoordinates);
            rawTurtleOperations.push_back(operation->clone());
        }
    }
    else // variable.hasEvaluation() - no other option
    {
        for(const auto &var : variable.getEvaluation())
            interpretVariableExecution(var);
        //TODO - detect endless recursion (variable evaluated to the same variable)
    }
}

void CodeAnalyzer::interpretTurtleOperationExecution(const parser_namespace::TurtleOperationExecution *statement)
{
    std::unique_ptr<TurtleOperation> operation(TurtleOperation::create(*statement->turtleOperation));
    operation->applyAndUpdateUtmostCoordinates(turtleState, utmostCoordinates);
    rawTurtleOperations.push_back(std::move(operation));
}
