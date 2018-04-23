#pragma once
#include <array>
#include <cstring>

class Source;

class Lexer
{
public:
    static constexpr int MAX_LITERAL_SIZE = 24;
    static constexpr int NUMBER_OF_KEYWORDS = 13;
    static constexpr int MAX_KEYWORD_LENGTH = 9;
    struct Literal : public std::array<char, MAX_LITERAL_SIZE>
    {
        Literal()
        {
            std::memset(data(), 0, MAX_LITERAL_SIZE);
        }

        Literal(const char *str)
        {
            std::memset(data(), 0, MAX_LITERAL_SIZE);
            std::strncpy(data(), str, MAX_LITERAL_SIZE -1);
        }
    };

    enum Symbol : char
    {
        error, end_of_text, int_number, float_number, literal,
        forward_keyword, rotate_keyword, penup_keyword, pendown_keyword,
        pencolour_keyword, goto_keyword, pensize_keyword, scale_keyword, pushstate_keyword,
        popstate_keyword, evaluate_keyword, execute_keyword, redefine_keyword,
        production_operator, equals_symbol = '=', plus_symbol = '+', l_curly_bracket_symbol = '{',
        r_curly_bracket_symbol = '}', l_round_bracket_symbol = '(', r_round_bracket_symbol = ')',
        semicolon_symbol = ';', colon_symbol = ','
    };

    Lexer(Source &source);
    Symbol getNextToken();
    Literal getLastReadLiteral() const; // return by VALUE (it is just 16 bytes)
    int getLastReadInt() const;
    float getLastReadFloat() const;
    const Source& getSource() const;

private:
    Source &src;
    Literal lastReadLiteral;
    int lastReadInt;
    float lastReadFloat;
    char c; // last read character, one AFTER last returned token

    struct Keyword
    {
        Symbol keyword;
        Literal string;
    };

    static const Keyword keywordHashTable[NUMBER_OF_KEYWORDS];

    Symbol getNextTokenInternalSwitch();
    Symbol readNumber(bool isnegative);
    Symbol readFloat(long long unsigned integer_part, bool isnegative);
    Symbol readWord();
    Symbol readLiteral(Literal &str);
};
