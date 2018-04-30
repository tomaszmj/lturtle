#include "lexer.h"
#include "source.h"
#include "exception.h"
#include <iostream>
#include <memory>

std::ostream& operator<<(std::ostream &os, const Lexer::TokenPtr &token);

int main(int argc, char **argv)
{
    (void) argc;
    (void) argv;
    std::ios_base::sync_with_stdio(false); // see: https://stackoverflow.com/questions/9371238/why-is-reading-lines-from-stdin-much-slower-in-c-than-python?rq=1
    try
    {
        Source src(std::cin);
        Lexer lex(src);
        std::cout << "Found tokens:\n";
        Lexer::TokenPtr token;
        do
        {
            token = lex.getNextToken();
            std::cout << token;
        } while(token->getSymbol() != Lexer::end_of_text && token->getSymbol() != Lexer::error);
        return 0;
    }
    catch(const Exception &ex)
    {
        std::cout << ex.what();
        return -1;
    }
}

std::ostream& operator<<(std::ostream &os, const Lexer::TokenPtr &token)
{
    switch(token->getSymbol())
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
    if(token->getSymbol() == Lexer::literal)
        std::cout << " (" << token->getLiteral() << ")\n";
    else if(token->getSymbol() == Lexer::int_number)
        std::cout << " (" << token->getInt() << ")\n";
    else if(token->getSymbol() == Lexer::float_number)
        std::cout << " (" << token->getFloat() << ")\n";
    else
        std::cout << "\n";
    return os;
}

