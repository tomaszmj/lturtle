#pragma once
#include <istream>
#include <fstream>

class Source
{
public:
    Source(std::istream &is);
    Source(const char *filename);
    char getNextChar();
    unsigned getLine() const;
    unsigned getPosition() const;

private:
    std::ifstream file; // might be unused - see constructiors
    std::istream &input;
    unsigned line;
    unsigned position;
};
