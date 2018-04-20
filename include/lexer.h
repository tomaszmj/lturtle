#pragma once
#include <array>

class Source;

class Lexer
{
public:
    constexpr int MAX_LITERAL_SIZE = 16;

    enum Symbol
    {
        equals_symbol, production_symbol, plus_symbol, l_sqare_bracket_symbol,
        r_square_bracket_symbol, l_round_bracket_symbol, r_round_bracket_symbol,
        semicolon_symbol, colon_symbol, int_number, float_number, literal,
        forward_keyword, rotate_keyword, penup_keyword, pendown_keyword,
        pencolour_keyword, goto_keyword, pensize_keyword, scale_keyword, pushstate_keyword,
        popstate_keyword, evaluate_keyword, execute_keyword, redefine_keyword, end_of_text
    };

    Lexer(Source &source);
    Symbol getNextToken();
    const std::array<char, MAX_LITERAL_SIZE>& getLastReadLiteral() const;
    int getLastReadInt() const;
    float getLastReadFloat() const;

private:
    Source &src;
    std::array<char, MAX_LITERAL_SIZE> lastReadLiteral;
    int lastReadInt;
    float lastReadFloat;
};
