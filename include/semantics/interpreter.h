#pragma once
#include "lexer.h"
#include "parser.h"
#include "syntax_tree.h"
#include "drawing_context.h"
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
    lexer_namespace::Lexer lexer;
    parser_namespace::Parser parser;
    DrawingContext drawingContext;
    TurtleState turtleState;
    VariableMap variableMap;

    void interpret(const parser_namespace::Statement &statement);
};

}
