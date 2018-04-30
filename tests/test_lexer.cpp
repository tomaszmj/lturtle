#include "source.h"
#include "lexer.h"
#include "exception.h"
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
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Lexer::equals_symbol);
    Lexer::TokenPtr t = lex.getNextToken();
    BOOST_REQUIRE(t->getSymbol() == Lexer::int_number && t->getInt() == -123);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Lexer::semicolon_symbol);
    BOOST_REQUIRE_THROW(lex.getNextToken()->getSymbol(), LexerException);
}


BOOST_AUTO_TEST_CASE( get_next_token_symbols_and_operator )
{
    const std::string input = "=+{ }  (  ) ;,->+ # =";
    std::istringstream istr(input);
    Source src(istr);
    Lexer lex(src);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Lexer::equals_symbol);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Lexer::plus_symbol);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Lexer::l_curly_bracket_symbol);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Lexer::r_curly_bracket_symbol);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Lexer::l_round_bracket_symbol);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Lexer::r_round_bracket_symbol);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Lexer::semicolon_symbol);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Lexer::colon_symbol);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Lexer::production_operator);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Lexer::plus_symbol);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Lexer::end_of_text);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Lexer::end_of_text); // repeat on purpose
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Lexer::end_of_text); // repeat on purpose
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
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Lexer::forward_keyword);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Lexer::rotate_keyword);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Lexer::penup_keyword);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Lexer::pendown_keyword);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Lexer::pencolour_keyword);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Lexer::goto_keyword);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Lexer::colon_symbol);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Lexer::pensize_keyword);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Lexer::scale_keyword);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Lexer::production_operator);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Lexer::pushstate_keyword);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Lexer::popstate_keyword);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Lexer::evaluate_keyword);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Lexer::plus_symbol);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Lexer::execute_keyword);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Lexer::redefine_keyword);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Lexer::end_of_text);
}

BOOST_AUTO_TEST_CASE( get_next_token_literals )
{
    const std::string input = R"(
        x abcd->execut_e a12345678901234567890123
        kkk;a123456789012345678901234
    )";
    std::istringstream istr(input);
    Source src(istr);
    Lexer lex(src);
    Lexer::TokenPtr t = lex.getNextToken();
    BOOST_REQUIRE(t->getSymbol() == Lexer::literal && t->getLiteral() == "x");
    t = lex.getNextToken();
    BOOST_REQUIRE(t->getSymbol() == Lexer::literal && t->getLiteral() == "abcd");
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Lexer::production_operator);
    t = lex.getNextToken();
    BOOST_REQUIRE(t->getSymbol() == Lexer::literal && t->getLiteral() == "execut_e");
    t = lex.getNextToken();
    BOOST_REQUIRE(t->getSymbol() == Lexer::literal && t->getLiteral() == "a12345678901234567890123");
    t = lex.getNextToken();
    BOOST_REQUIRE(t->getSymbol() == Lexer::literal && t->getLiteral() == "kkk");
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Lexer::semicolon_symbol);
    BOOST_REQUIRE_THROW(lex.getNextToken(), LexerException); // too long literal
}

BOOST_AUTO_TEST_CASE( get_next_token_numbers )
{
    const std::string input = "0,1234 0.1 -1.000001 -23 00";
    std::istringstream istr(input);
    Source src(istr);
    Lexer lex(src);
    Lexer::TokenPtr t = lex.getNextToken();
    BOOST_REQUIRE(t->getSymbol() == Lexer::int_number && t->getInt() == 0);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Lexer::colon_symbol);
    t = lex.getNextToken();
    BOOST_REQUIRE(t->getSymbol() == Lexer::int_number && t->getInt() == 1234);
    t = lex.getNextToken();
    BOOST_REQUIRE(t->getSymbol() == Lexer::float_number && t->getFloat() == 0.1f);
    t = lex.getNextToken();
    BOOST_REQUIRE(t->getSymbol() == Lexer::float_number && t->getFloat() == -1.000001f);
    t = lex.getNextToken();
    BOOST_REQUIRE(t->getSymbol() == Lexer::int_number && t->getInt() == -23);
    BOOST_REQUIRE_THROW(lex.getNextToken()->getSymbol(), LexerException);
}

BOOST_AUTO_TEST_CASE( get_next_token_numbers_error1 )
{
    const std::string input = "3000000000";
    std::istringstream istr(input);
    Source src(istr);
    Lexer lex(src);
    BOOST_REQUIRE_THROW(lex.getNextToken(), LexerException);
}

BOOST_AUTO_TEST_CASE( get_next_token_numbers_error2 )
{
    const std::string input = "0.00000000000000000000000000000000000000000000000000000000000000000000000000000000000000001";
    std::istringstream istr(input);
    Source src(istr);
    Lexer lex(src);
    BOOST_REQUIRE_THROW(lex.getNextToken(), LexerException);
}

BOOST_AUTO_TEST_CASE( get_next_token_numbers_error3 )
{
    const std::string input = "0.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
    std::istringstream istr(input);
    Source src(istr);
    Lexer lex(src);
    BOOST_REQUIRE_THROW(lex.getNextToken(), LexerException);
}
