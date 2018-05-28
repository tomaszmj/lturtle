#pragma once
#include <istream>

namespace semantics_namespace
{

class Interpreter
{
public:
    static void run(std::istream &input, const std::string output_filename);
};

}
