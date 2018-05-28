#include "interpreter.h"
#include "code_analyzer.h"
#include "exception.h"

using namespace semantics_namespace;

void Interpreter::run(std::istream &input, const std::string output_filename)
{
    std::vector<std::unique_ptr<TurtleOperation>> raw_turtle_operations;
    UtmostTurtleCoordinates utmost_turtle_coordinates;
    {
        CodeAnalyzer code_analyzer(input);
        raw_turtle_operations = code_analyzer.moveRawTurtleOperations();
        utmost_turtle_coordinates = code_analyzer.getUtmostCoordinates();
    }
    DrawingContext context(utmost_turtle_coordinates);
    TurtleState state;
    for(auto &operation : raw_turtle_operations)
        operation->applyAndDraw(state, context);
    context.save(output_filename);
}
