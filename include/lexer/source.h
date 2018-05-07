#pragma once
#include <istream>

namespace lexer_namespace
{

class Source
{
public:
    struct Position
    {
        unsigned line;
        unsigned inLine;
        long long unsigned inFile;

        Position();
        Position(const Position &p);
        std::string toString() const;
    };

    Source(std::istream &is);
    char next();
    char c() const;
    const Position &getPosition() const;

private:
    std::istream &input;
    Position position;
    char currentChar;
};

}
