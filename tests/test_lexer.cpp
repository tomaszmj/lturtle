#include "source.h"
#include "lexer.h"
#include <string>
#include <sstream>
#define BOOST_TEST_MODULE lexer
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE( my_test )
{
    const std::string input = R"(
    = # dskf '][ #-3454 *-85+3  ]

                              -123 # ]''\;
            # fdg
        ;
    )";
    std::istringstream istr(input);
    Source src(istr);
    Lexer lex(src);
    BOOST_CHECK(lex.getNextToken() == Lexer::equals_symbol);
    BOOST_CHECK(lex.getNextToken() == Lexer::int_number);
    BOOST_CHECK(lex.getLastReadInt() == -123);
    BOOST_CHECK(lex.getNextToken() == Lexer::semicolon_symbol);
}
