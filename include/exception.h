#pragma once
#include <exception>
#include <string>

class Lexer;

class Exception : public std::exception
{
public:
    Exception(std::string &&message);
    virtual const char* what() const noexcept;
protected:
    std::string msg;
};

class LexerException : public Exception
{
public:
    LexerException(const Lexer &lex, std::string &&message);
};
