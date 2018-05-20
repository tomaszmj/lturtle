#include "interpreter.h"

using namespace semantics_namespace;

Interpreter::Interpreter(std::istream &input, const std::string output_filename)
{

}

void Interpreter::run()
{

}

CodeAnalyzer::CodeAnalyzer(std::istream &input)
    : source(input), lexer(source), parser(lexer)
{}

std::vector<std::unique_ptr<TurtleOperation>> &&CodeAnalyzer::interpret()
{
    std::unique_ptr<parser_namespace::Statement> statement;
    while((statement = parser.parseStatement()) != nullptr)
    {
        switch(statement->getType())
        {
            case parser_namespace::Statement::operation:
            case parser_namespace::Statement::production:
            case parser_namespace::Statement::evaluation:
                variableMap.define(*dynamic_cast<parser_namespace::Definition*>(statement.get()));
                break;
            case parser_namespace::Statement::literal_execution:
                interpretLiteralExecution(dynamic_cast<parser_namespace::LiteralExecution*>(statement.get()));
                break;
            case parser_namespace::Statement::turtle_operation_execution:
                interpretTurtleOperationExecution(dynamic_cast<parser_namespace::TurtleOperationExecution*>(statement.get()));
                break;
        }
    }
    return std::move(turtleOperationsToReturn);
}

UtmostTurtleCoordinates &CodeAnalyzer::getUtmostCoordinates()
{
    return coords;
}

void CodeAnalyzer::interpretLiteralExecution(const parser_namespace::LiteralExecution *statement)
{
    for(const std::unique_ptr<lexer_namespace::Token> &literal_token : statement->literals->literalsVector)
    {
        const Variable &variable = variableMap.get(literal_token->getLiteral());
        interpretVariableExecution(variable);
    }
}

void CodeAnalyzer::interpretVariableExecution(const Variable &variable)
{
    if(variable.hasOperations())
    {
        for(const std::unique_ptr<TurtleOperation> &operation : variable.getOperations())
        {
            operation->apply(turtleState);
            turtleOperationsToReturn.push_back(operation->clone());
        }
    }
    else // variable.hasEvaluation() - no other option
    {
        for(const auto &var : variable.getEvaluation())
            interpretVariableExecution(var);
        //TODO - detect endless recursion (varable evaluated to the same variable)
    }
}

void CodeAnalyzer::interpretTurtleOperationExecution(const parser_namespace::TurtleOperationExecution *statement)
{
    std::unique_ptr<TurtleOperation> operation(TurtleOperation::create(*statement->turtleOperation));
    operation->apply(turtleState);
    turtleOperationsToReturn.push_back(std::move(operation));
}
