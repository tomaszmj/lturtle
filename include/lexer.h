#pragma once
#include "source.h"
#include <string>
#include <memory>

class Lexer
{
public:
    static constexpr int MAX_LITERAL_LENGTH = 24;
    static constexpr int NUMBER_OF_KEYWORDS = 13;
    static constexpr int MAX_KEYWORD_LENGTH = 9;

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

    struct TokenValue
    {
        virtual ~TokenValue() {}
    };

    struct TokenValueInt : public TokenValue
    {
        TokenValueInt(int i) : number(i) {}
        int number;
    };

    struct TokenValueFloat : public TokenValue
    {
        TokenValueFloat(float f) : number(f) {}
        float number;
    };

    struct TokenValueString : public TokenValue
    {
        TokenValueString(std::string s) : string(s) {}
        std::string string;
    };

    class Token
    {
        friend class Lexer;
    public:
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
        std::unique_ptr<TokenValue> value;
    };

    using TokenPtr = std::unique_ptr<Token>;

    Lexer(Source &source);
    const Source &getSource() const;
    TokenPtr getNextToken();

private:
    Source &src;
    TokenPtr token;

    struct Keyword
    {
        Symbol keyword;
        std::string string;
    };

    static const Keyword keywordHashTable[NUMBER_OF_KEYWORDS];

    void skipWhitespaceAndComments();
    bool skipWhitespace();
    bool skipComment();
    void createNewToken();
    TokenPtr releaseToken(Symbol token_type);
    TokenPtr readOneCharacterSymbol();
    TokenPtr readProductionOperatorOrNumber();
    TokenPtr readEndOfText();
    TokenPtr readWordOrNumber();
    TokenPtr readNumber(bool isnegative);
    TokenPtr readNumberStartingWith0(bool isnegative);
    TokenPtr readFloat(long long unsigned integer_part, bool isnegative);
    TokenPtr readWord();
    TokenPtr readLiteral();
};
