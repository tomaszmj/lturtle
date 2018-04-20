#include "lexer.h"

Lexer::Lexer(Source &source)
{

}

Lexer::Symbol Lexer::getNextToken()
{

}

const std::array<char, Lexer::MAX_LITERAL_SIZE> &Lexer::getLastReadLiteral() const
{
    return lastReadLiteral;
}

int Lexer::getLastReadInt() const
{
    return lastReadInt;
}

float Lexer::getLastReadFloat() const
{
    return lastReadFloat;
}
