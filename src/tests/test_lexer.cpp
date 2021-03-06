#include "source.h"
#include "lexer.h"
#include "exception.h"
#include <string>
#include <sstream>
#define BOOST_TEST_MODULE lexer
#include <boost/test/unit_test.hpp>

using namespace lexer_namespace;

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
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Token::equals_symbol);
    Lexer::TokenPtr t = lex.getNextToken();
    BOOST_REQUIRE(t->getSymbol() == Token::int_number && t->getInt() == -123);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Token::semicolon_symbol);
    BOOST_REQUIRE_THROW(lex.getNextToken()->getSymbol(), LexerException);
}


BOOST_AUTO_TEST_CASE( get_next_token_symbols_and_operator )
{
    const std::string input = "=+{ }  (  ) ;,->+ # =";
    std::istringstream istr(input);
    Source src(istr);
    Lexer lex(src);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Token::equals_symbol);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Token::plus_symbol);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Token::l_curly_bracket_symbol);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Token::r_curly_bracket_symbol);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Token::l_round_bracket_symbol);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Token::r_round_bracket_symbol);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Token::semicolon_symbol);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Token::colon_symbol);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Token::production_operator);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Token::plus_symbol);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Token::end_of_text);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Token::end_of_text); // repeat on purpose
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Token::end_of_text); // repeat on purpose
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
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Token::forward_keyword);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Token::rotate_keyword);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Token::penup_keyword);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Token::pendown_keyword);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Token::pencolour_keyword);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Token::goto_keyword);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Token::colon_symbol);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Token::pensize_keyword);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Token::scale_keyword);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Token::production_operator);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Token::pushstate_keyword);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Token::popstate_keyword);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Token::evaluate_keyword);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Token::plus_symbol);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Token::execute_keyword);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Token::redefine_keyword);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Token::end_of_text);
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
    BOOST_REQUIRE(t->getSymbol() == Token::literal && t->getLiteral() == "x");
    t = lex.getNextToken();
    BOOST_REQUIRE(t->getSymbol() == Token::literal && t->getLiteral() == "abcd");
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Token::production_operator);
    t = lex.getNextToken();
    BOOST_REQUIRE(t->getSymbol() == Token::literal && t->getLiteral() == "execut_e");
    t = lex.getNextToken();
    BOOST_REQUIRE(t->getSymbol() == Token::literal && t->getLiteral() == "a12345678901234567890123");
    t = lex.getNextToken();
    BOOST_REQUIRE(t->getSymbol() == Token::literal && t->getLiteral() == "kkk");
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Token::semicolon_symbol);
    BOOST_REQUIRE_THROW(lex.getNextToken(), LexerException); // too long literal
}

BOOST_AUTO_TEST_CASE( get_next_token_numbers )
{
    const std::string input = "0,1234 0.1 -1.000001 -23 00";
    std::istringstream istr(input);
    Source src(istr);
    Lexer lex(src);
    Lexer::TokenPtr t = lex.getNextToken();
    BOOST_REQUIRE(t->getSymbol() == Token::int_number && t->getInt() == 0);
    BOOST_REQUIRE(lex.getNextToken()->getSymbol() == Token::colon_symbol);
    t = lex.getNextToken();
    BOOST_REQUIRE(t->getSymbol() == Token::int_number && t->getInt() == 1234);
    t = lex.getNextToken();
    BOOST_REQUIRE(t->getSymbol() == Token::float_number && t->getFloat() == 0.1f);
    t = lex.getNextToken();
    BOOST_REQUIRE(t->getSymbol() == Token::float_number && t->getFloat() == -1.000001f);
    t = lex.getNextToken();
    BOOST_REQUIRE(t->getSymbol() == Token::int_number && t->getInt() == -23);
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
