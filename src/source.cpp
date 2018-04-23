#include "source.h"
#include "exception.h"

Source::Source(std::istream &is)
    : input(is), line(0), position(0)
{}

Source::Source(const char *filename)
    : file(filename), input(file), line(0), position(0)
{
    if(!file)
        throw Exception("Error - cannot open file " + std::string(filename));
}

char Source::getNextChar()
{
    if(!input)
        return -1;
    char c = input.get();
    if(c == '\n')
    {
        position = 0;
        ++line;
    }
    else
        ++position;
    return c;
}

unsigned Source::getLine() const
{
    return line;
}

unsigned Source::getPosition() const
{
    return position;
}
