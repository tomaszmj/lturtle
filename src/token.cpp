#include "token.h"
#include "exception.h"

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
#ifdef DEBUG
    if(symbol != int_number)
        throw Exception("token does not contain int number");
#endif
    return reinterpret_cast<ValueInt*>(value.get())->number;
}

float Token::getFloat() const
{
#ifdef DEBUG
    if(symbol != float_number)
        throw Exception("token does not contain float number");
#endif
    return reinterpret_cast<ValueFloat*>(value.get())->number;
}

const std::string &Token::getLiteral() const
{
#ifdef DEBUG
    if(symbol != literal)
        throw Exception("token does not contain literal");
#endif
    return reinterpret_cast<ValueString*>(value.get())->string;
}
