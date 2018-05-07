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

std::vector<std::unique_ptr<TurtleOperation>> &&CodeAnalyzer::interpret(UtmostTurtleCoordinates &coords)
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
                //todo
                break;
            case parser_namespace::Statement::turtle_operation_execution:
                //todo
                break;
        }
    }
    return std::move(turtleOperationsToReturn);
}
