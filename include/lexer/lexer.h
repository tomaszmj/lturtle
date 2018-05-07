#pragma once
#include "source.h"
#include "token.h"
#include <string>
#include <memory>

namespace lexer_namespace
{

class Lexer
{
public:
    static constexpr int MAX_LITERAL_LENGTH = 24;
    static constexpr int NUMBER_OF_KEYWORDS = 13;
    static constexpr int MAX_KEYWORD_LENGTH = 9;

    using TokenPtr = std::unique_ptr<Token>;

    Lexer(Source &source);
    const Source &getSource() const;
    TokenPtr getNextToken();

private:
    Source &src;
    TokenPtr token;

    struct Keyword
    {
        Token::Symbol keyword;
        std::string string;
    };

    static const Keyword keywordHashTable[NUMBER_OF_KEYWORDS];

    void skipWhitespaceAndComments();
    bool skipWhitespace();
    bool skipComment();
    void createNewToken();
    TokenPtr releaseToken(Token::Symbol token_type);
    TokenPtr readOneCharacterSymbol();
    TokenPtr readProductionOperatorOrNumber();
    TokenPtr readEndOfText();
    TokenPtr readWordOrNumber();
    TokenPtr readNumber(bool isnegative);
    TokenPtr readNumberStartingWith0(bool isnegative);
    TokenPtr readFloat(long long unsigned integer_part, bool isnegative);
    TokenPtr readWord();
};

}
