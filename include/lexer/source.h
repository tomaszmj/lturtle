#pragma once
#include <istream>

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
