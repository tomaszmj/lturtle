#include "error_handler.h"
#include "lexer.h"
#include "source.h"

Exception::Exception(std::string &&msg)
    : msg(msg)
{}

const char *Exception::what() const
{
    return msg.c_str();
}

LexerException::LexerException(const Lexer &lex, std::string &&msg)
{
    message = "Lexer error (line " + std::to_string(lex.getSource().getLine()) +
              ", position " + lex.getSource().getPosition() + "):\n" + msg;
}
