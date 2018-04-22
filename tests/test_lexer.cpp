#include "source.h"
#include "lexer.h"
#include <string>
#include <sstream>
#define BOOST_TEST_MODULE lexer
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_CASE( get_next_token_random )
{
    const std::string input = R"(
    = # dskf '][ #-3454 *-85+3  ]

                              -123 # ]''\;
            # fdg
        ;
            00100
    )";
    std::istringstream istr(input);
    Source src(istr);
    Lexer lex(src);
    BOOST_CHECK(lex.getNextToken() == Lexer::equals_symbol);
    BOOST_CHECK(lex.getNextToken() == Lexer::int_number);
    BOOST_CHECK(lex.getLastReadInt() == -123);
    BOOST_CHECK(lex.getNextToken() == Lexer::semicolon_symbol);
    BOOST_CHECK(lex.getNextToken() == Lexer::error);
}


BOOST_AUTO_TEST_CASE( get_next_token_symbols_and_operator )
{
    const std::string input = "=+{ }  (  ) ;,->";
    std::istringstream istr(input);
    Source src(istr);
    Lexer lex(src);
    BOOST_CHECK(lex.getNextToken() == Lexer::equals_symbol);
    BOOST_CHECK(lex.getNextToken() == Lexer::plus_symbol);
    BOOST_CHECK(lex.getNextToken() == Lexer::l_curly_bracket_symbol);
    BOOST_CHECK(lex.getNextToken() == Lexer::r_curly_bracket_symbol);
    BOOST_CHECK(lex.getNextToken() == Lexer::l_round_bracket_symbol);
    BOOST_CHECK(lex.getNextToken() == Lexer::r_round_bracket_symbol);
    BOOST_CHECK(lex.getNextToken() == Lexer::semicolon_symbol);
    BOOST_CHECK(lex.getNextToken() == Lexer::colon_symbol);
    BOOST_CHECK(lex.getNextToken() == Lexer::production_operator);
}

