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
    TurtleState turtleState;
    DrawingContext drawingContext;
};

class CodeAnalyzer
{
public:
    CodeAnalyzer(std::istream &input);

    // returns vector of raw turtle operations (after evaluating all variables etc.) and fills in StartingData
    std::vector<std::unique_ptr<TurtleOperation>> &&interpret(UtmostTurtleCoordinates &coords);

private:
    lexer_namespace::Source source;
    lexer_namespace::Lexer lexer;
    parser_namespace::Parser parser;
    TurtleState turtleState;
    VariableMap variableMap;
    std::vector<std::unique_ptr<TurtleOperation>> turtleOperationsToReturn;
};

}
