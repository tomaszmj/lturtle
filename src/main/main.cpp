#include "lexer.h"
#include "source.h"
#include "parser.h"
#include "exception.h"
#include <iostream>
#include <memory>

std::ostream& operator<<(std::ostream &os, const lexer::Lexer::TokenPtr &token);
void run_lexer_test();
void run_parser_test();

int main(int argc, char **argv)
{
    (void) argc;
    (void) argv;
    std::ios_base::sync_with_stdio(false); // see: https://stackoverflow.com/questions/9371238/why-is-reading-lines-from-stdin-much-slower-in-c-than-python?rq=1
    try
    {
        run_parser_test();
        return 0;
    }
    catch(const Exception &ex)
    {
        std::cout << ex.what();
        return -1;
    }
}

std::ostream& operator<<(std::ostream &os, const lexer::Lexer::TokenPtr &token)
{
    switch(token->getSymbol())
    {
        case lexer::Token::error: os << "error"; break;
        case lexer::Token::end_of_text: os << "end_of_text"; break;
        case lexer::Token::int_number: os << "int_number"; break;
        case lexer::Token::float_number: os << "float_number"; break;
        case lexer::Token::literal: os << "literal"; break;
        case lexer::Token::forward_keyword: os << "forward_keyword"; break;
        case lexer::Token::rotate_keyword: os << "rotate_keyword"; break;
        case lexer::Token::penup_keyword: os << "penup_keyword"; break;
        case lexer::Token::pendown_keyword: os << "pendown_keyword"; break;
        case lexer::Token::pencolour_keyword: os << "pencolour_keyword"; break;
        case lexer::Token::goto_keyword: os << "goto_keyword"; break;
        case lexer::Token::pensize_keyword: os << "pensize_keyword"; break;
        case lexer::Token::scale_keyword: os << "scale_keyword"; break;
        case lexer::Token::pushstate_keyword: os << "pushstate_keyword"; break;
        case lexer::Token::popstate_keyword: os << "popstate_keyword"; break;
        case lexer::Token::evaluate_keyword: os << "evaluate_keyword"; break;
        case lexer::Token::execute_keyword: os << "execute_keyword"; break;
        case lexer::Token::redefine_keyword: os << "redefine_keyword"; break;
        case lexer::Token::production_operator: os << "production_operator"; break;
        case lexer::Token::equals_symbol: os << "equals_symbol"; break;
        case lexer::Token::plus_symbol: os << "plus_symbol"; break;
        case lexer::Token::l_curly_bracket_symbol: os << "l_curly_bracket_symbol"; break;
        case lexer::Token::r_curly_bracket_symbol: os << "r_curly_bracket_symbol"; break;
        case lexer::Token::l_round_bracket_symbol: os << "l_round_bracket_symbol"; break;
        case lexer::Token::r_round_bracket_symbol: os << "r_round_bracket_symbol"; break;
        case lexer::Token::semicolon_symbol: os << "semicolon_symbol"; break;
        case lexer::Token::colon_symbol: os << "colon_symbol"; break;
    }   
    if(token->getSymbol() == lexer::Token::literal)
        std::cout << " (" << token->getLiteral() << ")\n";
    else if(token->getSymbol() == lexer::Token::int_number)
        std::cout << " (" << token->getInt() << ")\n";
    else if(token->getSymbol() == lexer::Token::float_number)
        std::cout << " (" << token->getFloat() << ")\n";
    else
        std::cout << "\n";
    return os;
}

void run_lexer_test()
{
    lexer::Source src(std::cin);
    lexer::Lexer lex(src);
    std::cout << "Found tokens:\n";
    lexer::Lexer::TokenPtr token;
    do
    {
        token = lex.getNextToken();
        std::cout << token;
    } while(token->getSymbol() != lexer::Token::end_of_text && token->getSymbol() != lexer::Token::error);
}

void run_parser_test()
{
    lexer::Source src(std::cin);
    lexer::Lexer lex(src);
    parser::Parser parser(lex);
    auto program = parser.parseProgram();
    std::cout << program->toString();
}
