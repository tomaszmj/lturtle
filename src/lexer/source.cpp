#include "source.h"
#include "exception.h"

Source::Position::Position()
    : line(1), inLine(0), inFile(0)
{}

Source::Position::Position(const Source::Position &p)
    : line(p.line), inLine(p.inLine), inFile(p.inFile)
{}

Source::Source(std::istream &is)
    : input(is)
{}

char Source::next()
{
    if(!input)
        return -1;
    currentChar = input.get();
    ++position.inFile;
    if(currentChar == '\n')
    {
        position.inLine = 0;
        ++position.line;
    }
    else
        ++position.inLine;
    return currentChar;
}

char Source::c() const
{
    return currentChar;
}

const Source::Position &Source::getPosition() const
{
    return position;
}
