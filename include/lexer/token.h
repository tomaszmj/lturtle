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
        virtual std::string toString() const = 0;
    };

    struct ValueInt : public Value
    {
        int number;

        ValueInt(int i) : number(i) {}
        virtual std::string toString() const;
    };

    struct ValueFloat : public Value
    {
        float number;

        ValueFloat(float f) : number(f) {}
        virtual std::string toString() const;
    };

    struct ValueString : public Value
    {
        std::string string;

        ValueString(std::string s) : string(s) {}
        virtual std::string toString() const;
    };

    Token(const Source::Position &begin);
    Symbol getSymbol() const;
    const Source::Position &getPositionBegin() const;
    const Source::Position &getPositionEnd() const;
    int getInt() const;
    float getFloat() const;
    const std::string &getLiteral() const;
    std::string toString() const;
    static std::string typeToString(Symbol s);

private:
    Source::Position positionBegin;
    Source::Position positionEnd;
    Symbol symbol;
    std::unique_ptr<Value> value;
};
