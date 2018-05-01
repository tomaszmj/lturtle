#pragma once
#include "source.h"
#include <string>
#include <memory>

class Token
{
    friend class Lexer;
public:
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

    struct Value
    {
        virtual ~Value() {}
    };

    struct ValueInt : public Value
    {
        ValueInt(int i) : number(i) {}
        int number;
    };

    struct ValueFloat : public Value
    {
        ValueFloat(float f) : number(f) {}
        float number;
    };

    struct ValueString : public Value
    {
        ValueString(std::string s) : string(s) {}
        std::string string;
    };

    Token(const Source::Position &begin);
    Symbol getSymbol() const;
    const Source::Position &getPositionBegin() const;
    const Source::Position &getPositionEnd() const;
    int getInt() const;
    float getFloat() const;
    const std::string &getLiteral() const;

private:
    Source::Position positionBegin;
    Source::Position positionEnd;
    Symbol symbol;
    std::unique_ptr<Value> value;
};
