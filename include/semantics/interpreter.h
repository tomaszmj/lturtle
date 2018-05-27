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

}
