#include "source.h"
#include "lexer.h"
#include "exception.h"
#include "parser.h"
#include <string>
#include <sstream>
#define BOOST_TEST_MODULE lexer
#include <boost/test/unit_test.hpp>

using namespace parser_namespace;

#define INIT_BOILERPLATE \
    std::istringstream istr(input); \
    lexer::Source src(istr); \
    lexer::Lexer lex(src); \
    Parser parser(lex);

// parseTurtleOperationArguments - tested in parseTurtleOperation

BOOST_AUTO_TEST_CASE(parseTurtleOperation)
{
    const std::string input = R"(
    forward(1.0);
    forward(1);
    rotate(-1.0);
    penup();
    pendown();
    pencolour(255, 0, 0);
    goto(12.0, -132);
    pensize(5);
    scale(10.0);
    pushstate();
    popstate();
    )";
    INIT_BOILERPLATE
    auto program = parser_namespace.parseProgram();
    std::string str = program->toString();
    BOOST_REQUIRE(program->toString() == R"(forward(1.0000);
forward(1);
rotate(-1.0000);
penup();
pendown();
pencolour(255, 0, 0);
goto(12.0000, -132);
pensize(5);
scale(10.0000);
pushstate();
popstate();
)");
}

// parseLiteralString - tested in parseProduction, parseEvaluation and parseLiteralExecution

BOOST_AUTO_TEST_CASE(parseEvaluation)
{
    const std::string input = R"(
    x = evaluate(4, a+bc +   d);
    )";
    INIT_BOILERPLATE
    auto st = parser_namespace.parseStatement();
    BOOST_REQUIRE(st->toString() == "x = evaluate(4, a + bc + d)");
}

BOOST_AUTO_TEST_CASE(parseEvaluation_redefine)
{
    const std::string input = R"(
    redefine     x = evaluate(4, a+bc +   d);
    )";
    INIT_BOILERPLATE
    auto st = parser_namespace.parseStatement();
    BOOST_REQUIRE(st->toString() == "redefine x = evaluate(4, a + bc + d)");
}


BOOST_AUTO_TEST_CASE(parseOperation_empty)
{
    const std::string input = R"(
    xxx = {};
    )";
    INIT_BOILERPLATE
    auto st = parser_namespace.parseStatement();
    BOOST_REQUIRE(st->toString() == "xxx = { }");
}

BOOST_AUTO_TEST_CASE(parseOperation_empty_redefine)
{
    const std::string input = R"(
    redefine     xxx={};
    )";
    INIT_BOILERPLATE
    auto st = parser_namespace.parseStatement();
    BOOST_REQUIRE(st->toString() == "redefine xxx = { }");
}

BOOST_AUTO_TEST_CASE(parseOperation_nonempty)
{
    const std::string input = R"(
    xxx= { pushstate();  # comment
    pendown(); };
    )";
    INIT_BOILERPLATE
    auto st = parser_namespace.parseStatement();
    BOOST_REQUIRE(st->toString() == "xxx = { pushstate(); pendown(); }");
}

BOOST_AUTO_TEST_CASE(parseOperation_nonempty_redefine)
{
    const std::string input = R"(redefine
    xxx= { pushstate();  # comment
    pendown(); };
    )";
    INIT_BOILERPLATE
    auto st = parser_namespace.parseStatement();
    BOOST_REQUIRE(st->toString() == "redefine xxx = { pushstate(); pendown(); }");
}

// parseOperationOrEvaluation - tested in parseOperation and parseEvaluation

BOOST_AUTO_TEST_CASE(parseProduction)
{
    const std::string input = R"(
aaa -> x   + y + z ;
    )";
    INIT_BOILERPLATE
    auto st = parser_namespace.parseStatement();
    BOOST_REQUIRE(st->toString() == "aaa -> x + y + z");
}

BOOST_AUTO_TEST_CASE(parseProduction_redefine)
{
    const std::string input = R"(redefine
aaa -> x   + y + z ;
    )";
    INIT_BOILERPLATE
    auto st = parser_namespace.parseStatement();
    BOOST_REQUIRE(st->toString() == "redefine aaa -> x + y + z");
}

// parseTurtleOperationExecution - tested in parseTurtleOperation

BOOST_AUTO_TEST_CASE(parseLiteralExecution)
{
    const std::string input = R"(
    execute(x+aa);
    )";
    INIT_BOILERPLATE
    auto st = parser_namespace.parseStatement();
    BOOST_REQUIRE(st->toString() == "execute(x + aa)");
}

// parseDefinition - tested in parseDefinition

// parseStatement - tested in all the tests

BOOST_AUTO_TEST_CASE(parseProgram_example)
{
    const std::string input = R"(
    s0 =     {   forward(1.0); };  # comment
    s1 = { forward(2.0); };
    left = { pushstate(); rotate(-45.0); };
    right = { popstate(); rotate(45.0); };
    s1 -> s1 + s1;
    s0 -> s1 + left + s0 + right + s0;
    tree3 = evaluate(3, s0);
    pencolour(0, 255, 0);
    execute(tree3);
    )";
    INIT_BOILERPLATE
    auto program = parser_namespace.parseProgram();
    std::string str = program->toString();
    BOOST_REQUIRE(program->toString() ==
R"(s0 = { forward(1.0000); };
s1 = { forward(2.0000); };
left = { pushstate(); rotate(-45.0000); };
right = { popstate(); rotate(45.0000); };
s1 -> s1 + s1;
s0 -> s1 + left + s0 + right + s0;
tree3 = evaluate(3, s0);
pencolour(0, 255, 0);
execute(tree3);
)");
}

BOOST_AUTO_TEST_CASE(error_consume)
{
    const std::string input = "execute(x+aa)+;";
    INIT_BOILERPLATE
    auto predicate = [](const ParserException &e) { return std::string(e.what()).find("at token '+'") != std::string::npos; };
    BOOST_CHECK_EXCEPTION(parser_namespace.parseStatement(), ParserException, predicate);
}

BOOST_AUTO_TEST_CASE(error_accept)
{
    const std::string input = "x = evaluate(3, a+b+22";
    INIT_BOILERPLATE
    auto predicate = [](const ParserException &e) { return std::string(e.what()).find("expected token types: literal") != std::string::npos; };
    BOOST_CHECK_EXCEPTION(parser_namespace.parseStatement(), ParserException, predicate);
}

BOOST_AUTO_TEST_CASE(error_parseDefinition)
{
    const std::string input = "x () ;";
    INIT_BOILERPLATE
    auto predicate = [](const ParserException &e) { return std::string(e.what()).find("expected '=' or '->'") != std::string::npos; };
    BOOST_CHECK_EXCEPTION(parser_namespace.parseStatement(), ParserException, predicate);
}

BOOST_AUTO_TEST_CASE(error_parseOperationOrEvaluation)
{
    const std::string input = "x = a;";
    INIT_BOILERPLATE
    auto predicate = [](const ParserException &e) {
        return std::string(e.what()).find("expected '{' and turtle operations or 'evaluate' and evaluation arguments") != std::string::npos; };
    BOOST_CHECK_EXCEPTION(parser_namespace.parseStatement(), ParserException, predicate);
}

BOOST_AUTO_TEST_CASE(error_parseTurtleOperation)
{
    const std::string input = "x = { forward(1.0); aaaaa(); };";
    INIT_BOILERPLATE
    auto predicate = [](const ParserException &e) {
        return std::string(e.what()).find("expected one of turtle operation keywords") != std::string::npos; };
    BOOST_CHECK_EXCEPTION(parser_namespace.parseStatement(), ParserException, predicate);
}

#undef INIT_BOILERPLATE
