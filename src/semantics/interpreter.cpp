#include "interpreter.h"
#include "code_analyzer.h"
#include "exception.h"
#include "iostream"

using namespace semantics_namespace;

void Interpreter::run(std::istream &input, const std::string output_filename)
{
    std::vector<std::unique_ptr<TurtleOperation>> raw_turtle_operations;
    UtmostTurtleCoordinates utmost_turtle_coordinates(std::pair<float, float>(0, 0));
    {
        CodeAnalyzer code_analyzer(input);
        raw_turtle_operations = code_analyzer.moveRawTurtleOperations();
        utmost_turtle_coordinates = code_analyzer.getUtmostCoordinates();
    } // deleting CodeAnalyzer, with its parser, variable map etc. - it is no longer needed
    if(!TurtleOperation::emptyStateStack())
        std::cerr << "warning - state stack nonempty (number of pushstate operations was greater than number of popstate operations)\n";
    DrawingContext context(utmost_turtle_coordinates);
    TurtleState state;
    for(auto &operation : raw_turtle_operations)
    context.save(output_filename);
}
