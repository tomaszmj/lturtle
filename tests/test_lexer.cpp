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
    BOOST_REQUIRE(lex.getNextToken() == Lexer::equals_symbol);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::int_number);
    BOOST_REQUIRE(lex.getLastReadInt() == -123);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::semicolon_symbol);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::error);
}


BOOST_AUTO_TEST_CASE( get_next_token_symbols_and_operator )
{
    const std::string input = "=+{ }  (  ) ;,->+ # =";
    std::istringstream istr(input);
    Source src(istr);
    Lexer lex(src);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::equals_symbol);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::plus_symbol);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::l_curly_bracket_symbol);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::r_curly_bracket_symbol);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::l_round_bracket_symbol);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::r_round_bracket_symbol);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::semicolon_symbol);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::colon_symbol);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::production_operator);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::plus_symbol);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::end_of_text);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::end_of_text); // repeat on purpose
    BOOST_REQUIRE(lex.getNextToken() == Lexer::end_of_text); // repeat on purpose
}

BOOST_AUTO_TEST_CASE( get_next_token_keywords )
{
    const std::string input = R"(
        forward rotate penup pendown pencolour # IGNORE IT
goto,pensize scale->pushstate popstate
        evaluate+execute   redefine
    )";
    std::istringstream istr(input);
    Source src(istr);
    Lexer lex(src);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::forward_keyword);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::rotate_keyword);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::penup_keyword);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::pendown_keyword);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::pencolour_keyword);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::goto_keyword);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::colon_symbol);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::pensize_keyword);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::scale_keyword);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::production_operator);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::pushstate_keyword);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::popstate_keyword);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::evaluate_keyword);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::plus_symbol);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::execute_keyword);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::redefine_keyword);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::end_of_text);
}

BOOST_AUTO_TEST_CASE( get_next_token_literals )
{
    const std::string input = R"(
        x abcd->execut_e a1234567890123456789012
        kkk;a12345678901234567890123
    )";
    std::istringstream istr(input);
    Source src(istr);
    Lexer lex(src);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::literal);
    BOOST_REQUIRE(lex.getLastReadLiteral() == Lexer::Literal("x"));
    BOOST_REQUIRE(lex.getNextToken() == Lexer::literal);
    BOOST_REQUIRE(lex.getLastReadLiteral() == Lexer::Literal("abcd"));
    BOOST_REQUIRE(lex.getNextToken() == Lexer::production_operator);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::literal);
    BOOST_REQUIRE(lex.getLastReadLiteral() == Lexer::Literal("execut_e"));
    BOOST_REQUIRE(lex.getNextToken() == Lexer::literal);
    BOOST_REQUIRE(lex.getLastReadLiteral() == Lexer::Literal("a1234567890123456789012"));
    BOOST_REQUIRE(lex.getNextToken() == Lexer::literal);
    BOOST_REQUIRE(lex.getLastReadLiteral() == Lexer::Literal("kkk"));
    BOOST_REQUIRE(lex.getNextToken() == Lexer::semicolon_symbol);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::error); // too long literal
}

BOOST_AUTO_TEST_CASE( get_next_token_numbers )
{
    const std::string input = "0,1234 0.1 -1.000001 -23 00";
    std::istringstream istr(input);
    Source src(istr);
    Lexer lex(src);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::int_number);
    BOOST_REQUIRE(lex.getLastReadInt() == 0);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::colon_symbol);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::int_number);
    BOOST_REQUIRE(lex.getLastReadInt() == 1234);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::float_number);
    BOOST_REQUIRE(lex.getLastReadFloat() == 0.1f);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::float_number);
    BOOST_REQUIRE(lex.getLastReadFloat() == -1.000001f);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::int_number);
    BOOST_REQUIRE(lex.getLastReadInt() == -23);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::error);
}

BOOST_AUTO_TEST_CASE( get_next_token_numbers_error1 )
{
    const std::string input = "3000000000";
    std::istringstream istr(input);
    Source src(istr);
    Lexer lex(src);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::error);
}

BOOST_AUTO_TEST_CASE( get_next_token_numbers_error2 )
{
    const std::string input = "0.00000000000000000000000000000000000000000000000000000000000000000000000000000000000000001";
    std::istringstream istr(input);
    Source src(istr);
    Lexer lex(src);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::error);
}

BOOST_AUTO_TEST_CASE( get_next_token_numbers_error3 )
{
    const std::string input = "0.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    std::istringstream istr(input);
    Source src(istr);
    Lexer lex(src);
    BOOST_REQUIRE(lex.getNextToken() == Lexer::error);
}
