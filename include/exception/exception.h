#pragma once
#include <exception>
#include <string>

namespace lexer_namespace
{
class Lexer;
}

class Exception : public std::exception
{
public:
    Exception(std::string &&message);
    virtual const char *what() const noexcept;
protected:
    std::string msg;
};

class LexerException : public Exception
{
public:
    LexerException(const lexer_namespace::Lexer &lex, std::string &&message);
};

class ParserException : public Exception
{
public:
    ParserException(std::string &&message);
};

class SemanticsException : public Exception
{
public:
    SemanticsException(std::string &&message);
};
