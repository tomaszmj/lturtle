#include "lexer.h"
#include "source.h"
#include "parser.h"
#include "interpreter.h"
#include "exception.h"
#include <iostream>
#include <memory>

void print_help(char *program_name)
{
    std::cerr << "Usage: " << program_name << " <argument>\n"
                 "<argument> can be:\n"
                 "--lexer : runs only lexer test, giving list of tokens\n"
                 "--parser : runs only parser test, output should be the same as input, excluding comments and whitespace\n"
                 "(any other - output image filename) : runs interpreter, saving result in a file\n\n"
                 "Regardless of mode used, program uses standard input - in order to interpret file, redirect it, for example:\n" <<
                 program_name << " image.png <code.lturtle\n";
    std::exit(-1);
}

void run_lexer_test();
void run_parser_test();

int main(int argc, char **argv)
{
    std::ios_base::sync_with_stdio(false); // see: https://stackoverflow.com/questions/9371238/why-is-reading-lines-from-stdin-much-slower-in-c-than-python?rq=1
    if(argc != 2)
        print_help(argv[0]);
    try
    {
        if(std::string(argv[1]) == "--lexer")
            run_lexer_test();
        else if(std::string(argv[1]) == "--parser")
            run_parser_test();
        else
            semantics_namespace::Interpreter::run(std::cin, argv[1]);
        return 0;
    }
    catch(const std::exception &ex)
    {
        std::cout << ex.what();
        return -2;
    }
}

std::ostream& operator<<(std::ostream &os, const lexer_namespace::Lexer::TokenPtr &token)
{
    switch(token->getSymbol())
    {
        case lexer_namespace::Token::error: os << "error"; break;
        case lexer_namespace::Token::end_of_text: os << "end_of_text"; break;
        case lexer_namespace::Token::int_number: os << "int_number"; break;
        case lexer_namespace::Token::float_number: os << "float_number"; break;
        case lexer_namespace::Token::literal: os << "literal"; break;
        case lexer_namespace::Token::forward_keyword: os << "forward_keyword"; break;
        case lexer_namespace::Token::rotate_keyword: os << "rotate_keyword"; break;
        case lexer_namespace::Token::penup_keyword: os << "penup_keyword"; break;
        case lexer_namespace::Token::pendown_keyword: os << "pendown_keyword"; break;
        case lexer_namespace::Token::pencolour_keyword: os << "pencolour_keyword"; break;
        case lexer_namespace::Token::goto_keyword: os << "goto_keyword"; break;
        case lexer_namespace::Token::pensize_keyword: os << "pensize_keyword"; break;
        case lexer_namespace::Token::scale_keyword: os << "scale_keyword"; break;
        case lexer_namespace::Token::pushstate_keyword: os << "pushstate_keyword"; break;
        case lexer_namespace::Token::popstate_keyword: os << "popstate_keyword"; break;
        case lexer_namespace::Token::evaluate_keyword: os << "evaluate_keyword"; break;
        case lexer_namespace::Token::execute_keyword: os << "execute_keyword"; break;
        case lexer_namespace::Token::redefine_keyword: os << "redefine_keyword"; break;
        case lexer_namespace::Token::production_operator: os << "production_operator"; break;
        case lexer_namespace::Token::equals_symbol: os << "equals_symbol"; break;
        case lexer_namespace::Token::plus_symbol: os << "plus_symbol"; break;
        case lexer_namespace::Token::l_curly_bracket_symbol: os << "l_curly_bracket_symbol"; break;
        case lexer_namespace::Token::r_curly_bracket_symbol: os << "r_curly_bracket_symbol"; break;
        case lexer_namespace::Token::l_round_bracket_symbol: os << "l_round_bracket_symbol"; break;
        case lexer_namespace::Token::r_round_bracket_symbol: os << "r_round_bracket_symbol"; break;
        case lexer_namespace::Token::semicolon_symbol: os << "semicolon_symbol"; break;
        case lexer_namespace::Token::colon_symbol: os << "colon_symbol"; break;
    }   
    if(token->getSymbol() == lexer_namespace::Token::literal)
        std::cout << " (" << token->getLiteral() << ")\n";
    else if(token->getSymbol() == lexer_namespace::Token::int_number)
        std::cout << " (" << token->getInt() << ")\n";
    else if(token->getSymbol() == lexer_namespace::Token::float_number)
        std::cout << " (" << token->getFloat() << ")\n";
    else
        std::cout << "\n";
    return os;
}

void run_lexer_test()
{
    lexer_namespace::Source src(std::cin);
    lexer_namespace::Lexer lex(src);
    std::cout << "Found tokens:\n";
    lexer_namespace::Lexer::TokenPtr token;
    do
    {
        token = lex.getNextToken();
        std::cout << token;
    } while(token->getSymbol() != lexer_namespace::Token::end_of_text && token->getSymbol() != lexer_namespace::Token::error);
}

void run_parser_test()
{
    lexer_namespace::Source src(std::cin);
    lexer_namespace::Lexer lex(src);
    parser_namespace::Parser parser(lex);
    auto program = parser.parseProgram();
    std::cout << program->toString();
}
