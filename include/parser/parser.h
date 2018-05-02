#pragma once
#include "syntax_tree.h"
#include "token.h"
#include <memory>

class Lexer;

class Parser
{
public:
    Parser(Lexer &lex);
    const Lexer &getLexer();
    std::unique_ptr<Program> parseProgram();

private:
    Lexer &lexer;
    std::unique_ptr<Token> t;

    void nextToken();
    void consume(Token::Symbol token_type);
    std::unique_ptr<Statement> parseStatement();
    std::unique_ptr<Statement> parseRedefinition();
    std::unique_ptr<Statement> parseDefinition();
    std::unique_ptr<Statement> parseLiteralExecution();
    std::unique_ptr<Statement> parseTurtleOperationExecution();
    std::unique_ptr<Statement> parseProduction();
    std::unique_ptr<Statement> parseOperationOrEvaluation();
    std::unique_ptr<Statement> parseOperation();
    std::unique_ptr<Statement> parseEvaluation();
    std::unique_ptr<LiteralString> parseLiteralString();
    std::unique_ptr<TurtleOperation> parseTurtleOperation();
};
