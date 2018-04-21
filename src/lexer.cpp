#include "lexer.h"


// Hashing system has been generated in scrpit auxiliary/hashpy
// To avoid collisions, size of hash table is larger than number of keywords
const Lexer::Keyword Lexer::keywordHashTable[]  =
{
    { error, Literal() },                           // 0 - unused
    { rotate_keyword, Literal("rotate") },          // 1
    { penup_keyword, Literal("penup") },            // 2
    { redefine_keyword, Literal("redefine") },      // 3
    { evaluate_keyword, Literal("evaluate") },      // 4
    { pencolour_keyword, Literal("pencolour") },    // 5
    { pushstate_keyword, Literal("pushstate") },    // 6
    { error, Literal() },                           // 7 - usused
    { popstate_keyword, Literal("popstate") },      // 8
    { execute_keyword, Literal("execute") },        // 9
    { scale_keyword, Literal("scale") },            // 10
    { error, Literal() },                           // 11 - unused
    { pendown_keyword, Literal("pendown") },        // 12
    { forward_keyword, Literal("forward") },        // 13
    { goto_keyword, Literal("goto") },              // 14
    { error, Literal() },                           // 15 - unused
    { pensize_keyword, Literal("pensize") }         // 16
};

Lexer::Lexer(Source &source)
    : src(source)
{

}

Lexer::Symbol Lexer::getNextToken()
{

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
