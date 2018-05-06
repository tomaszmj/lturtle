#include "lexer.h"
#include "source.h"
#include "parser.h"
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
        Parser parser(lex);
        auto program = parser.parseProgram();
        std::cout << program->toString();
//        std::cout << "Found tokens:\n";
//        Lexer::TokenPtr token;
//        do
//        {
//            token = lex.getNextToken();
//            std::cout << token;
//        } while(token->getSymbol() != Token::end_of_text && token->getSymbol() != Token::error);
//        return 0;
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
        case Token::error: os << "error"; break;
        case Token::end_of_text: os << "end_of_text"; break;
        case Token::int_number: os << "int_number"; break;
        case Token::float_number: os << "float_number"; break;
        case Token::literal: os << "literal"; break;
        case Token::forward_keyword: os << "forward_keyword"; break;
        case Token::rotate_keyword: os << "rotate_keyword"; break;
        case Token::penup_keyword: os << "penup_keyword"; break;
        case Token::pendown_keyword: os << "pendown_keyword"; break;
        case Token::pencolour_keyword: os << "pencolour_keyword"; break;
        case Token::goto_keyword: os << "goto_keyword"; break;
        case Token::pensize_keyword: os << "pensize_keyword"; break;
        case Token::scale_keyword: os << "scale_keyword"; break;
        case Token::pushstate_keyword: os << "pushstate_keyword"; break;
        case Token::popstate_keyword: os << "popstate_keyword"; break;
        case Token::evaluate_keyword: os << "evaluate_keyword"; break;
        case Token::execute_keyword: os << "execute_keyword"; break;
        case Token::redefine_keyword: os << "redefine_keyword"; break;
        case Token::production_operator: os << "production_operator"; break;
        case Token::equals_symbol: os << "equals_symbol"; break;
        case Token::plus_symbol: os << "plus_symbol"; break;
        case Token::l_curly_bracket_symbol: os << "l_curly_bracket_symbol"; break;
        case Token::r_curly_bracket_symbol: os << "r_curly_bracket_symbol"; break;
        case Token::l_round_bracket_symbol: os << "l_round_bracket_symbol"; break;
        case Token::r_round_bracket_symbol: os << "r_round_bracket_symbol"; break;
        case Token::semicolon_symbol: os << "semicolon_symbol"; break;
        case Token::colon_symbol: os << "colon_symbol"; break;
    }   
    if(token->getSymbol() == Token::literal)
        std::cout << " (" << token->getLiteral() << ")\n";
    else if(token->getSymbol() == Token::int_number)
        std::cout << " (" << token->getInt() << ")\n";
    else if(token->getSymbol() == Token::float_number)
        std::cout << " (" << token->getFloat() << ")\n";
    else
        std::cout << "\n";
    return os;
}
