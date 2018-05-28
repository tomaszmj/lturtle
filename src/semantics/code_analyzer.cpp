#include "code_analyzer.h"
#include "exception.h"
#include <set>

using namespace semantics_namespace;

CodeAnalyzer::CodeAnalyzer(std::istream &input)
    : source(input), lexer(source), parser(lexer), utmostCoordinates(std::pair<float, float>(0, 0))
{
    std::unique_ptr<parser_namespace::Statement> statement;
    unsigned i = 0;
    try
    {
        while((statement = parser.parseStatement()) != nullptr)
        {
            ++i;
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
    catch(std::logic_error &ex)
    {
        if(statement)
            throw SemanticsException(std::string(ex.what()) + " in statement (number " + std::to_string(i) + "):\n" + statement->toString());
        else
            throw SemanticsException(std::string(ex.what()) + " in undefined statement (number " + std::to_string(i) + ")\n");
    }
    catch(const std::bad_alloc&)
    {
        if(statement)
            throw SemanticsException("failed to allocate memory in statement (number" + std::to_string(i) + "):\n" + statement->toString());
        else
            throw SemanticsException("failed to allocate memory in undefined statement (number " + std::to_string(i) + ")\n");
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
        variablesBeingEvaluated.clear();
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
        auto it = variablesBeingEvaluated.find(&variable);
        if(it != variablesBeingEvaluated.end())
            throw std::logic_error("endless recursion detected - self-referring evaluation");
        variablesBeingEvaluated.insert(it, &variable);
        for(const auto &var : variable.getEvaluation())
            interpretVariableExecution(var);
    }
}

void CodeAnalyzer::interpretTurtleOperationExecution(const parser_namespace::TurtleOperationExecution *statement)
{
    std::unique_ptr<TurtleOperation> operation(TurtleOperation::create(*statement->turtleOperation));
    operation->applyAndUpdateUtmostCoordinates(turtleState, utmostCoordinates);
    rawTurtleOperations.push_back(std::move(operation));
}
