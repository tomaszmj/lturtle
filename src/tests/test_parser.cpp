#include "source.h"
#include "lexer.h"
#include "exception.h"
#include "parser.h"
#include <string>
#include <sstream>
#define BOOST_TEST_MODULE lexer
#include <boost/test/unit_test.hpp>

#define INIT_BOILERPLATE \
    std::istringstream istr(input); \
    Source src(istr); \
    Lexer lex(src); \
    Parser parser(lex);

// parseTurtleOperationArguments - tested in parseTurtleOperation

BOOST_AUTO_TEST_CASE(parseTurtleOperation)
{
    const std::string input = R"(
    )";
    INIT_BOILERPLATE
    auto program = parser.parseProgram();
    //BOOST_REQUIRE(program->toString() == "");
}

// parseLiteralString - tested in parseProduction, parseEvaluation and parseLiteralExecution

BOOST_AUTO_TEST_CASE(parseEvaluation)
{
    const std::string input = R"(
    x = evaluate(4, a+bc +   d);"
    )";
    INIT_BOILERPLATE
    auto st = parser.parseStatement();
    BOOST_REQUIRE(st->toString() == "x = evaluate( 4, a + bc + d )");
}

BOOST_AUTO_TEST_CASE(parseEvaluation_redefine)
{
    const std::string input = R"(
    redefine     x = evaluate(4, a+bc +   d);"
    )";
    INIT_BOILERPLATE
    auto st = parser.parseStatement();
    BOOST_REQUIRE(st->toString() == "redefine x = evaluate( 4, a + bc + d )");
}


BOOST_AUTO_TEST_CASE(parseOperation_empty)
{
    const std::string input = R"(
    xxx = {};
    )";
    INIT_BOILERPLATE
    auto st = parser.parseStatement();
    BOOST_REQUIRE(st->toString() == "xxx = { }");
}

BOOST_AUTO_TEST_CASE(parseOperation_empty_redefine)
{
    const std::string input = R"(
    redefine     xxx={};
    )";
    INIT_BOILERPLATE
    auto st = parser.parseStatement();
    BOOST_REQUIRE(st->toString() == "redefine xxx = { }");
}

BOOST_AUTO_TEST_CASE(parseOperation_nonempty)
{
    const std::string input = R"(
    xxx= { pushstate();  # comment
    pendown(); };
    )";
    INIT_BOILERPLATE
    auto st = parser.parseStatement();
    BOOST_REQUIRE(st->toString() == "xxx = { pushstate(); pendown(); }");
}

BOOST_AUTO_TEST_CASE(parseOperation_nonempty_redefine)
{
    const std::string input = R"(redefine
    xxx= { pushstate();  # comment
    pendown(); };
    )";
    INIT_BOILERPLATE
    auto st = parser.parseStatement();
    BOOST_REQUIRE(st->toString() == "redefine xxx = { pushstate(); pendown(); }");
}

// parseOperationOrEvaluation - tested in parseOperation and parseEvaluation

BOOST_AUTO_TEST_CASE(parseProduction)
{
    const std::string input = R"(
aaa -> x   + y + z ;
    )";
    INIT_BOILERPLATE
    auto st = parser.parseStatement();
    BOOST_REQUIRE(st->toString() == "aaa -> x + y + z");
}

BOOST_AUTO_TEST_CASE(parseProduction_redefine)
{
    const std::string input = R"(redefine
aaa -> x   + y + z ;
    )";
    INIT_BOILERPLATE
    auto st = parser.parseStatement();
    BOOST_REQUIRE(st->toString() == "redefine aaa -> x + y + z");
}

// parseTurtleOperationExecution - tested in parseTurtleOperation

BOOST_AUTO_TEST_CASE(parseLiteralExecution)
{
    const std::string input = R"(
    execute(x+aa);
    )";
    INIT_BOILERPLATE
    auto st = parser.parseStatement();
    BOOST_REQUIRE(st->toString() == "execute( x + aa )");
}

// parseDefinition - tested in parseDefinition

// parseStatement - tested in all the tests

BOOST_AUTO_TEST_CASE(parseProgram_example)
{
    const std::string input = R"(
    execute(x+aa);
    )";
    INIT_BOILERPLATE
    auto program = parser.parseProgram();
    BOOST_REQUIRE(program->toString() ==
R"(execute( x + aa );
)");
}

#undef INIT_BOILERPLATE