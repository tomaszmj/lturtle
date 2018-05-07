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

}
