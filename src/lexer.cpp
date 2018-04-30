#include "lexer.h"
#include "source.h"
#include "exception.h"
#include <iostream>
#include <cctype>
#include <limits>
#include <cmath>

Lexer::Token::Token(const Source::Position &begin)
    : positionBegin(begin), symbol(error)
{}

Lexer::Symbol Lexer::Token::getSymbol() const
{
    return symbol;
}

const Source::Position &Lexer::Token::getPositionBegin() const
{
    return positionBegin;
}

const Source::Position &Lexer::Token::getPositionEnd() const
{
    return positionEnd;
}

int Lexer::Token::getInt() const
{
#ifdef DEBUG
    if(symbol != int_number)
        throw Exception("token does not contain int number");
#endif
    return reinterpret_cast<TokenValueInt*>(value.get())->number;
}

float Lexer::Token::getFloat() const
{
#ifdef DEBUG
    if(symbol != float_number)
        throw Exception("token does not contain float number");
#endif
    return reinterpret_cast<TokenValueFloat*>(value.get())->number;
}

const std::string &Lexer::Token::getLiteral() const
{
#ifdef DEBUG
    if(symbol != literal)
        throw Exception("token does not contain literal");
#endif
    return reinterpret_cast<TokenValueString*>(value.get())->string;
}

// Hashing system has been generated in auxiliary subproject - hashtest
const Lexer::Keyword Lexer::keywordHashTable[Lexer::NUMBER_OF_KEYWORDS]  =
{
    { pencolour_keyword, "pencolour" },
    { forward_keyword, "forward" },
    { pendown_keyword, "pendown" },
    { scale_keyword, "scale" },
    { pushstate_keyword, "pushstate" },
    { execute_keyword, "execute" },
    { redefine_keyword, "redefine" },
    { rotate_keyword, "rotate" },
    { popstate_keyword, "popstate" },
    { penup_keyword, "penup" },
    { pensize_keyword, "pensize" },
    { evaluate_keyword, "evaluate" },
    { goto_keyword, "goto" }
};

Lexer::Lexer(Source &source)
    : src(source)
{
    src.next();
}

const Source &Lexer::getSource() const
{
    return src;
}

Lexer::TokenPtr Lexer::getNextToken()
{
    skipWhitespaceAndComments();
    createNewToken();
    switch(src.c())
    {
        case '=':
        case '+':
        case '{':
        case '}':
        case '(':
        case ')':
        case ';':
        case ',':
            return readOneCharacterSymbol();
        case '-':
            src.next();
            return readProductionOperatorOrNumber();
        case -1:
            return readEndOfText();
        default:
            return readWordOrNumber();
    }
}

void Lexer::skipWhitespaceAndComments()
{
    while(skipWhitespace() || skipComment())
        continue;
}

bool Lexer::skipWhitespace()
{
    if(!isspace(src.c()))
        return false;
    while(isspace(src.next()))
        continue;
    return true;
}

bool Lexer::skipComment()
{
    if(src.c() != '#')
        return false;
    do
    {
        if(src.next() == -1)
            return false; // end of text is treated as lack of comment so that skipWhitespaceAndComments() will end
    } while(src.c() != '\n');
    src.next();
    return true;
}

void Lexer::createNewToken()
{
    token.reset(new Token(src.getPosition()));
}

Lexer::TokenPtr Lexer::releaseToken(Symbol token_type)
{
    token->symbol = token_type;
    token->positionEnd = src.getPosition();
    return std::move(token);
}

Lexer::TokenPtr Lexer::readOneCharacterSymbol()
{
    Symbol symbol = static_cast<Lexer::Symbol>(src.c());
    src.next();
    return releaseToken(symbol);
}

Lexer::TokenPtr Lexer::readProductionOperatorOrNumber()
{
    if(src.c() == '>')
    {
        src.next();
        return releaseToken(production_operator);
    }
    else if(isdigit(src.c()))
        return readNumber(true);
    else
        throw LexerException(*this, "Unexpected character '" + std::string(1, src.c()) +
                             "' - excpected '>' or digit after '-'");

}

Lexer::TokenPtr Lexer::readEndOfText()
{
    return releaseToken(end_of_text);
}

Lexer::TokenPtr Lexer::readWordOrNumber()
{
    if(isdigit(src.c()))
        return readNumber(false);
    else if(isalpha(src.c()))
        return readWord();
    else
        throw LexerException(*this, "Unexpected character '" + std::string(1, src.c()) +
                                    "' -  there is no token starting with it");
}

Lexer::TokenPtr Lexer::readNumber(bool isnegative)
{
    if(src.c() == '0')
    {
        src.next();
        return readNumberStartingWith0(isnegative);
    }
    long long unsigned x = src.c() - '0';
    while(isdigit(src.next()))
    {
        x = x*10 + src.c() - '0';
        if(x > std::numeric_limits<int>::max())
            throw LexerException(*this, "Integer constant exceeding limit " +
                                        std::to_string(std::numeric_limits<int>::max()));
    }
    if(src.c() == '.')
    {
        src.next();
        return readFloat(x, isnegative);
    }
    int tmp = static_cast<int>(x);
    if(isnegative)
        tmp = -tmp;
    token->value.reset(new TokenValueInt(tmp));
    return releaseToken(int_number);
}

Lexer::TokenPtr Lexer::readNumberStartingWith0(bool isnegative)
{
    if(src.c() == '.')
    {
        src.next();
        return readFloat(0, isnegative);
    }
    else if(isdigit(src.c()))
        throw LexerException(*this, "Number cannot start with 0" + std::string(1, src.c()));
    token->value.reset(new TokenValueInt(0));
    return releaseToken(int_number);
}

Lexer::TokenPtr Lexer::readFloat(unsigned long long integer_part, bool isnegative)
{
    if(!isdigit(src.c()))
        throw LexerException(*this, "Unexpected character '" + std::string(1, src.c()) +
                             "' - excpected digit after '.'");
    long long unsigned x = src.c() - '0';
    src.next();
    int i = 1;
    while(isdigit(src.c()))
    {
        x = x*10 + src.c() - '0';
        ++i;
        if(i > std::numeric_limits<unsigned long long>::digits)
            throw LexerException(*this, "Floating point constant with too many digits after '.'");
        src.next();
    }
    double tmp = static_cast<double>(integer_part) + static_cast<double>(x) / static_cast<double>(std::pow(10, i));
    if(isnegative)
        tmp = -tmp;
    token->value.reset(new TokenValueFloat(static_cast<float>(tmp)));
    return releaseToken(float_number);
}

Lexer::TokenPtr Lexer::readWord()
{
    std::string str;
    uint32_t hash = 0;
    do
    {
        hash = (hash*3 + 651) ^ (static_cast<uint32_t>(src.c())*23);
        str.append(1, src.c());
        src.next();
        if(str.length() > MAX_LITERAL_LENGTH)
            throw LexerException(*this, "Too long name '" + str + "' - max accepted length is " +
                                 std::to_string(MAX_LITERAL_LENGTH));
    } while(isalpha(src.c()) || isdigit(src.c()) || src.c() == '_');
    hash = hash % NUMBER_OF_KEYWORDS;
    if(str.length() <= MAX_KEYWORD_LENGTH && keywordHashTable[hash].string == str)
        return releaseToken(keywordHashTable[hash].keyword);
    token->value.reset(new TokenValueString(str));
    return releaseToken(literal);
}

Lexer::TokenPtr Lexer::readLiteral()
{
//    int first_free_index = MAX_KEYWORD_LENGTH + 1;
//    for(;;)
//    {
//        str[first_free_index - 1] = c;
//        c = src.next();
//        if(!isalpha(c) && !isdigit(c) && c != '_')
//            break;

//    }
//    lastReadLiteral = str;
    return releaseToken(error);
}
