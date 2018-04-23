#include "lexer.h"
#include "source.h"
#include <iostream>
#include <cctype>
#include <limits>

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
    c = src.getNextChar();
}

Lexer::Symbol Lexer::getNextToken()
{
    for(;;)
    {
        while(isspace(c))
            c = src.getNextChar();
        Symbol sym = getNextTokenInternalSwitch();
        if(sym != -1) // if there was no comment
            return sym;
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

const Source &Lexer::getSource() const
{
   return src;
}

Lexer::Symbol Lexer::getNextTokenInternalSwitch()
{
    Symbol tmp_symbol;
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
            tmp_symbol = static_cast<Symbol>(c);
            c = src.getNextChar();
            return tmp_symbol;
        case '-':
            c = src.getNextChar();
            if(c == '>')
            {
                c = src.getNextChar();
                return production_operator;
            }
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
            c = src.getNextChar();
            return static_cast<Symbol>(-1); // special value incidating that there was comment and new token needs to be found
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

Lexer::Symbol Lexer::readNumber(bool isnegative)
{
    if(c == '0')
    {
        c = src.getNextChar();
        if(c == '.')
            return readFloat(0, isnegative);
        else if(isdigit(c))
            return error;
        lastReadInt = 0;
        return int_number;
    }
    long long unsigned x = c - '0';
    while(isdigit(c = src.getNextChar()))
    {
        x = x*10 + c - '0';
        if(x > std::numeric_limits<int>::max())
            return error;
    }
    if(c == '.')
        return readFloat(x, isnegative);
    lastReadInt = static_cast<int>(x);
    if(isnegative)
        lastReadInt = -lastReadInt;
    return int_number;
}

Lexer::Symbol Lexer::readFloat(unsigned long long integer_part, bool isnegative)
{
    double x = static_cast<double>(integer_part);
    double digit_weight = 0.1;
    c = src.getNextChar();
    if(!isdigit(c))
        return error;
    do
    {
        x += digit_weight * static_cast<double>(c - '0');
        digit_weight *= 0.1;
        if(digit_weight < std::numeric_limits<float>::denorm_min())
            return error;
    } while(isdigit(c = src.getNextChar()));
    lastReadFloat = static_cast<float>(x);
    if(isnegative)
        lastReadFloat = -lastReadFloat;
    return float_number;
}

Lexer::Symbol Lexer::readWord()
{
    Literal str;
    int first_free_index = 1;
    uint32_t hash = 0;
    for(;;)
    {
        hash = (hash*3 + 651) ^ (static_cast<uint32_t>(c)*23);
        str[first_free_index - 1] = c;
        c = src.getNextChar();
        if(!isalpha(c) && !isdigit(c) && c != '_')
            break;
        if(++first_free_index == MAX_LITERAL_SIZE)
            return error;
        else if(first_free_index > MAX_KEYWORD_LENGTH) // hash is no longer needed
            return readLiteral(str);
    }
    hash = hash % NUMBER_OF_KEYWORDS;
    if(keywordHashTable[hash].string == str)
        return keywordHashTable[hash].keyword;
    lastReadLiteral = str;
    return literal;
}

Lexer::Symbol Lexer::readLiteral(Lexer::Literal &str)
{
    int first_free_index = MAX_KEYWORD_LENGTH + 1;
    for(;;)
    {
        str[first_free_index - 1] = c;
        c = src.getNextChar();
        if(!isalpha(c) && !isdigit(c) && c != '_')
            break;
        if(++first_free_index == MAX_LITERAL_SIZE)
            return error;
    }
    lastReadLiteral = str;
    return literal;
}

