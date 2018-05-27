#pragma once
#include "lexer.h"
#include "parser.h"
#include "syntax_tree.h"
#include "turtle_operation.h"
#include "drawing_helpers.h"
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
    //DrawingContext drawingContext;
};

}
