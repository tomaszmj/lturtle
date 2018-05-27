#include "code_analyzer.h"
#include "exception.h"
#include <string>
#include <sstream>
#define BOOST_TEST_MODULE semantics
#include <boost/test/unit_test.hpp>

using namespace semantics_namespace;

BOOST_AUTO_TEST_CASE(variable_defineOperation_empty)
{
    const std::string input = R"(
        x = {};
    )";
    std::istringstream iss(input);
    CodeAnalyzer ca(iss);
    const VariableMap &vm = ca.getVariableMap();
    const Variable *x = vm.find("x");
    BOOST_REQUIRE(x != nullptr);
    BOOST_REQUIRE(vm.find("a") == nullptr);
    BOOST_REQUIRE(x->hasOperations() && !x->hasProduction() && !x->hasEvaluation());
    BOOST_REQUIRE(x->getOperations().size() == 0);
    auto v = ca.moveRawTurtleOperations();
    BOOST_REQUIRE(v.size() == 0);
}

BOOST_AUTO_TEST_CASE(variable_defineOperation_nonempty_and_execute)
{
    const std::string input = R"(
        x = { forward(1); pushstate(); };
        execute(x); # do it 2 times - for purpose
        execute(x);
    )";
    std::istringstream iss(input);
    CodeAnalyzer ca(iss);
    const VariableMap &vm = ca.getVariableMap();
    const Variable *x = vm.find("x");
    BOOST_REQUIRE(x != nullptr);
    BOOST_REQUIRE(x->hasOperations() && !x->hasProduction() && !x->hasEvaluation());
    BOOST_REQUIRE(x->getOperations().size() == 2);
    auto v = ca.moveRawTurtleOperations();
    BOOST_REQUIRE(v.size() == 4);
}

BOOST_AUTO_TEST_CASE(variable_defineProduction)
{
    const std::string input = R"(
        x = { forward(1); pushstate(); };
        y = {};
        y -> x+y+x;
    )";
    std::istringstream iss(input);
    CodeAnalyzer ca(iss);
    const VariableMap &vm = ca.getVariableMap();
    const Variable *x = vm.find("x");
    const Variable *y = vm.find("y");
    BOOST_REQUIRE(x != nullptr && y != nullptr);
    BOOST_REQUIRE(y->hasOperations() && y->hasProduction() && !y->hasEvaluation());
    const std::vector<std::reference_wrapper<Variable>> production = y->getProduction();
    BOOST_REQUIRE(production.size() == 3);
    BOOST_REQUIRE(x == &production[0].get());
    BOOST_REQUIRE(y == &production[1].get());
    BOOST_REQUIRE(x == &production[2].get());
}

BOOST_AUTO_TEST_CASE(variable_defineEvaluation)
{
    const std::string input = R"(
        x = { forward(1); pushstate(); };
        y = {};
        y -> x+y+x;
        z = evaluate(2, y);
    )";
    std::istringstream iss(input);
    CodeAnalyzer ca(iss);
    const VariableMap &vm = ca.getVariableMap();
    const Variable *x = vm.find("x");
    const Variable *y = vm.find("y");
    const Variable *z = vm.find("z");
    BOOST_REQUIRE(!z->hasOperations() && !z->hasProduction() && z->hasEvaluation());
    const std::vector<std::reference_wrapper<Variable>> evaluation = z->getEvaluation();
    BOOST_REQUIRE(evaluation.size() == 5);
    BOOST_REQUIRE(x == &evaluation[0].get());
    BOOST_REQUIRE(x == &evaluation[1].get());
    BOOST_REQUIRE(y == &evaluation[2].get());
    BOOST_REQUIRE(x == &evaluation[3].get());
    BOOST_REQUIRE(x == &evaluation[4].get());
}

BOOST_AUTO_TEST_CASE(variable_defineEvaluation_and_execute)
{
    const std::string input = R"(
        x = { forward(1); };
        y = {};
        y -> x+y+x;
        z = evaluate(2, y);
        pensize(2.0);
        execute(z);
    )";
    std::istringstream iss(input);
    CodeAnalyzer ca(iss);
    auto v = ca.moveRawTurtleOperations();
    BOOST_REQUIRE(v.size() == 5);
    BOOST_REQUIRE(dynamic_cast<TurtleOperationPensize*>(v[0].get()) != nullptr);
    BOOST_REQUIRE(dynamic_cast<TurtleOperationForward*>(v[1].get()) != nullptr);
    BOOST_REQUIRE(dynamic_cast<TurtleOperationForward*>(v[2].get()) != nullptr);
    BOOST_REQUIRE(dynamic_cast<TurtleOperationForward*>(v[3].get()) != nullptr);
    BOOST_REQUIRE(dynamic_cast<TurtleOperationForward*>(v[4].get()) != nullptr);
}

BOOST_AUTO_TEST_CASE(variable_defineEvaluation_redefineOperation_and_execute)
{
    const std::string input = R"(
        x = { forward(1); };
        y = {};
        y -> x+y+x;
        z = evaluate(2, y);
        pensize(2.0);
        redefine x = { rotate(1.5); }; # it SHOULD have impact on the result, despite being defeined after 'evaluate'
        execute(z);
    )";
    std::istringstream iss(input);
    CodeAnalyzer ca(iss);
    auto v = ca.moveRawTurtleOperations();
    BOOST_REQUIRE(v.size() == 5);
    BOOST_REQUIRE(dynamic_cast<TurtleOperationPensize*>(v[0].get()) != nullptr);
    BOOST_REQUIRE(dynamic_cast<TurtleOperationRotate*>(v[1].get()) != nullptr);
    BOOST_REQUIRE(dynamic_cast<TurtleOperationRotate*>(v[2].get()) != nullptr);
    BOOST_REQUIRE(dynamic_cast<TurtleOperationRotate*>(v[3].get()) != nullptr);
    BOOST_REQUIRE(dynamic_cast<TurtleOperationRotate*>(v[4].get()) != nullptr);
}

BOOST_AUTO_TEST_CASE(variable_defineEvaluation_redefineProduction_and_execute)
{
    const std::string input = R"(
        x = { forward(1); };
        y = {};
        y -> x+y+x;
        z = evaluate(2, y);
        pensize(2.0);
        redefine y -> x+y+x+z; # it should NOT have impact on the result
        execute(z);
    )";
    std::istringstream iss(input);
    CodeAnalyzer ca(iss);
    auto v = ca.moveRawTurtleOperations();
    BOOST_REQUIRE(v.size() == 5);
    BOOST_REQUIRE(dynamic_cast<TurtleOperationPensize*>(v[0].get()) != nullptr);
    BOOST_REQUIRE(dynamic_cast<TurtleOperationForward*>(v[1].get()) != nullptr);
    BOOST_REQUIRE(dynamic_cast<TurtleOperationForward*>(v[2].get()) != nullptr);
    BOOST_REQUIRE(dynamic_cast<TurtleOperationForward*>(v[3].get()) != nullptr);
    BOOST_REQUIRE(dynamic_cast<TurtleOperationForward*>(v[4].get()) != nullptr);
}

