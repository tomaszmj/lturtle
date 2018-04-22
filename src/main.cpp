#include "lexer.h"
#include "source.h"
#include <iostream>
#include <sstream>

const std::string input = R"(
= # dskf '][ #-3454 *-85+3  ]

                          123 # ]''\;
        # fdg
    ;
)";

int main(int argc, char **argv)
{
    std::istringstream istr(input);
    Source src(istr);
    Lexer lex(src);
    if(lex.getNextToken() == Lexer::equals_symbol)
        std::cout << "equals ok\n";
    if(lex.getNextToken() == Lexer::int_number)
        std::cout << "int number: " << lex.getLastReadInt() << "\n";
    if(lex.getNextToken() == Lexer::semicolon_symbol)
        std::cout << "semicolon ok\n";
    return 0;
}
