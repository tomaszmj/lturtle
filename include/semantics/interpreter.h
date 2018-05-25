#pragma once
#include "lexer.h"
#include "parser.h"
#include "syntax_tree.h"
#include "drawing_context.h"
#include "turtle_operation.h"
#include "turtle_state.h"
#include "variable.h"
#include <istream>

namespace semantics_namespace
{

class Interpreter
{
public:
    Interpreter(std::istream &input, const std::string output_filename);
    void run();

private:
    DrawingContext drawingContext;
};

class CodeAnalyzer
{
public:
    // CodeAnalyzer fills in all the data in the constructor.
    // After getting utomstCoordinates and rawTurtleOperations it can be destroyed.
    CodeAnalyzer(std::istream &input);

    std::vector<std::unique_ptr<TurtleOperation>> &&moveRawTurtleOperations();
    UtmostTurtleCoordinates getUtmostCoordinates();

private:
    lexer_namespace::Source source;
    lexer_namespace::Lexer lexer;
    parser_namespace::Parser parser;
    VariableMap variableMap;
    TurtleState turtleState;
    UtmostTurtleCoordinates utomstCoordinates;
    std::vector<std::unique_ptr<TurtleOperation>> rawTurtleOperations; // (after evaluating all variables etc.)

    void interpretLiteralExecution(const parser_namespace::LiteralExecution *statement);
    void interpretVariableExecution(const Variable &variable);
    void interpretTurtleOperationExecution(const parser_namespace::TurtleOperationExecution *statement);
};

}
