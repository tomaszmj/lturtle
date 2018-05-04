#include "exception.h"
#include "lexer.h"
#include "source.h"

Exception::Exception(std::string &&message)
    : msg(message + "\n")
{}

const char *Exception::what() const noexcept
{
    return msg.c_str();
}

LexerException::LexerException(const Lexer &lex, std::string &&msg)
    : Exception("Lexer error (" + lex.getSource().getPosition().toString() + ": " + msg)
{}

ParserException::ParserException(std::string &&message)
    : Exception("Parser error: " + message)
{}
