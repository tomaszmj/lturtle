#include "exception.h"
#include "lexer.h"
#include "token.h"
#include "source.h"

Exception::Exception(std::string &&message)
    : msg(message + "\n")
{}

const char *Exception::what() const noexcept
{
    return msg.c_str();
}

LexerException::LexerException(const lexer_namespace::Lexer &lex, std::string &&msg)
    : Exception("Lexer error (" + lex.getSource().getPosition().toString() + ": " + msg)
{}

ParserException::ParserException(std::string &&message)
    : Exception("Parser error: " + message)
{}

SemanticsException::SemanticsException(std::string &&message)
    : Exception("Semantic error: " + message)
{}

SemanticsException::SemanticsException(std::string &&message, const lexer_namespace::Token &literal)
    : Exception("Semantic error: " + message +
                "\n(from " + literal.getPositionBegin().toString() + " to " + literal.getPositionEnd().toString() + ")")
{}
