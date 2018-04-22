#pragma once
#include <istream>

class Source
{
public:
    Source(std::istream &is);
    char getNextChar();
    unsigned getLine() const;
    unsigned getPosition() const;

private:
    std::istream &input;
    unsigned line;
    unsigned position;
};
