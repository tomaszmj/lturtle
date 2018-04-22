#include "lexer.h"
#include "source.h"
#include <iostream>
#include <cctype>

// Hashing system has been generated in auxiliary subproject - hashtest
const Lexer::Keyword Lexer::keywordHashTable[Lexer::NUMBER_OF_KEYWORDS]  =
{
    { pencolour_keyword, Literal("pencolour") },
    { forward_keyword, Literal("forward") },
    { pendown_keyword, Literal("pendown") },
    { scale_keyword, Literal("scale") },
    { pushstate_keyword, Literal("pushstate") },
    { execute_keyword, Literal("execute") },
    { redefine_keyword, Literal("redefine") },
    { rotate_keyword, Literal("rotate") },
    { popstate_keyword, Literal("popstate") },
    { penup_keyword, Literal("penup") },
    { pensize_keyword, Literal("pensize") },
    { evaluate_keyword, Literal("evaluate") },
    { goto_keyword, Literal("goto") }
};

Lexer::Lexer(Source &source)
    : src(source)
{
}

Lexer::Symbol Lexer::getNextToken()
{
    for(;;)
    {
        do
        {
            c = src.getNextChar();
        } while(isspace(c));
        switch(c)
        {
            case '=':
            case '+':
            case '{':
            case '}':
            case '(':
            case ')':
            case ';':
            case ',':
                return static_cast<Symbol>(c);
            case '-':
                c = src.getNextChar();
                if(c == '>')
                    return production_operator;
                else if(isdigit(c))
                    return readNumber(true);
                else
                    return error; // error handling will be changed
            case '#':
                do
                {
                    c = src.getNextChar();
                    if(c == -1)
                        return end_of_text;
                } while(c != '\n');
                continue;
            case -1:
                return end_of_text;
            default:
                if(isdigit(c))
                    return readNumber(false);
                else if(isalpha(c))
                    return readWord();
                else
                    return error;
        }
    }
}

Lexer::Literal Lexer::getLastReadLiteral() const
{
    return lastReadLiteral;
}

int Lexer::getLastReadInt() const
{
    return lastReadInt;
}

float Lexer::getLastReadFloat() const
{
    return lastReadFloat;
}

int Lexer::getHash(Lexer::Literal string)
{
    uint32_t h = 0;
    for(char c : string)
    {
        if(c == 0)
            break;
        h = (h*3 + 651) ^ (static_cast<uint32_t>(c)*23);
    }
    return static_cast<uint32_t>(h % NUMBER_OF_KEYWORDS);
}

Lexer::Symbol Lexer::readNumber(bool isnegative)
{

}

Lexer::Symbol Lexer::readWord()
{

}
