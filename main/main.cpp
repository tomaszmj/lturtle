#include "lexer.h"
#include "source.h"
#include <iostream>

std::ostream& operator<<(std::ostream &os, Lexer::Symbol token);

int main(int argc, char **argv)
{
    std::ios_base::sync_with_stdio(false); // see: https://stackoverflow.com/questions/9371238/why-is-reading-lines-from-stdin-much-slower-in-c-than-python?rq=1
    if(argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <program file>\n";
        return -1;
    }
    Source src(argv[1]);
    Lexer lex(src);
    std::cout << "Found tokens:\n";
    Lexer::Symbol sym;
    do
    {
        sym = lex.getNextToken();
        std::cout << sym;
        if(sym == Lexer::literal)
            std::cout << " (" << lex.getLastReadLiteral().data() << ")\n";
        else if(sym == Lexer::int_number)
            std::cout << " (" << lex.getLastReadInt() << ")\n";
        else if(sym == Lexer::float_number)
            std::cout << " (" << lex.getLastReadFloat() << ")\n";
        else
            std::cout << "\n";
    } while(sym != Lexer::end_of_text && sym != Lexer::error);
    return 0;
}

std::ostream& operator<<(std::ostream &os, Lexer::Symbol token)
{
    switch(token)
    {
        case Lexer::error: os << "error"; break;
        case Lexer::end_of_text: os << "end_of_text"; break;
        case Lexer::int_number: os << "int_number"; break;
        case Lexer::float_number: os << "float_number"; break;
        case Lexer::literal: os << "literal"; break;
        case Lexer::forward_keyword: os << "forward_keyword"; break;
        case Lexer::rotate_keyword: os << "rotate_keyword"; break;
        case Lexer::penup_keyword: os << "penup_keyword"; break;
        case Lexer::pendown_keyword: os << "pendown_keyword"; break;
        case Lexer::pencolour_keyword: os << "pencolour_keyword"; break;
        case Lexer::goto_keyword: os << "goto_keyword"; break;
        case Lexer::pensize_keyword: os << "pensize_keyword"; break;
        case Lexer::scale_keyword: os << "scale_keyword"; break;
        case Lexer::pushstate_keyword: os << "pushstate_keyword"; break;
        case Lexer::popstate_keyword: os << "popstate_keyword"; break;
        case Lexer::evaluate_keyword: os << "evaluate_keyword"; break;
        case Lexer::execute_keyword: os << "execute_keyword"; break;
        case Lexer::redefine_keyword: os << "redefine_keyword"; break;
        case Lexer::production_operator: os << "production_operator"; break;
        case Lexer::equals_symbol: os << "equals_symbol"; break;
        case Lexer::plus_symbol: os << "plus_symbol"; break;
        case Lexer::l_curly_bracket_symbol: os << "l_curly_bracket_symbol"; break;
        case Lexer::r_curly_bracket_symbol: os << "r_curly_bracket_symbol"; break;
        case Lexer::l_round_bracket_symbol: os << "l_round_bracket_symbol"; break;
        case Lexer::r_round_bracket_symbol: os << "r_round_bracket_symbol"; break;
        case Lexer::semicolon_symbol: os << "semicolon_symbol"; break;
        case Lexer::colon_symbol: os << "colon_symbol"; break;
    }
    return os;
}

