#include "token.h"
#include "exception.h"
#include <sstream>
#include <iomanip>

using namespace lexer_namespace;

Token::Token(const Source::Position &begin)
    : positionBegin(begin), symbol(error)
{}

Token::Symbol Token::getSymbol() const
{
    return symbol;
}

const Source::Position &Token::getPositionBegin() const
{
    return positionBegin;
}

const Source::Position &Token::getPositionEnd() const
{
    return positionEnd;
}

int Token::getInt() const
{
    return dynamic_cast<ValueInt*>(value.get())->number;
}

float Token::getFloat() const
{
    if(symbol == int_number)
    {
        int tmp = dynamic_cast<ValueInt*>(value.get())->number;
        return static_cast<float>(tmp);
    }
    return dynamic_cast<ValueFloat*>(value.get())->number;
}

const std::string &Token::getLiteral() const
{
    return dynamic_cast<ValueString*>(value.get())->string;
}

std::string Token::toString() const
{
    switch(symbol)
    {
        case error:
            return "error";
        case end_of_text:
            return "end_of_text";
        case int_number:
        case float_number:
        case literal:
            return value->toString();
        case forward_keyword:
            return "forward";
        case rotate_keyword:
            return "rotate";
        case penup_keyword:
            return "penup";
        case pendown_keyword:
            return "pendown";
        case pencolour_keyword:
            return "pencolour";
        case goto_keyword:
            return "goto";
        case pensize_keyword:
            return "pensize";
        case scale_keyword:
            return "scale";
        case pushstate_keyword:
            return "pushstate";
        case popstate_keyword:
            return "popstate";
        case evaluate_keyword:
            return "evaluate";
        case execute_keyword:
            return "execute";
        case redefine_keyword:
            return "redefine";
        case production_operator:
            return "->";
        default:
            return std::string(1, symbol);
    }
}

std::string Token::typeToString(Token::Symbol s)
{
    switch(s)
    {
        case error:
            return "error";
        case end_of_text:
            return "end_of_text";
        case int_number:
            return "int";
        case float_number:
            return "float";
        case literal:
            return "literal";
        case forward_keyword:
            return "'forward'";
        case rotate_keyword:
            return "'rotate'";
        case penup_keyword:
            return "'penup'";
        case pendown_keyword:
            return "'pendown'";
        case pencolour_keyword:
            return "'pencolour'";
        case goto_keyword:
            return "'goto'";
        case pensize_keyword:
            return "'pensize'";
        case scale_keyword:
            return "'scale'";
        case pushstate_keyword:
            return "'pushstate'";
        case popstate_keyword:
            return "'popstate'";
        case evaluate_keyword:
            return "'evaluate'";
        case execute_keyword:
            return "'execute'";
        case redefine_keyword:
            return "'redefine'";
        case production_operator:
            return "'->'";
        default:
            return "'" + std::string(1, s) + "'";
    }
}

std::string Token::ValueInt::toString() const
{
    return std::to_string(number);
}

std::string Token::ValueFloat::toString() const
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(4) << number; // way of writing floats must be unified to enable testing
    return ss.str();
}

std::string Token::ValueString::toString() const
{
    return string;
}
