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
    std::unique_ptr<Token> currentToken;

    void nextToken();
    void consume(Token::Symbol token_type);
    std::unique_ptr<Token> accept(Token::Symbol token_type);

    std::unique_ptr<Statement> parseStatement();
    std::unique_ptr<Definition> parseRedefinition();
    std::unique_ptr<Definition> parseDefinition();
    std::unique_ptr<LiteralExecution> parseLiteralExecution();
    std::unique_ptr<TurtleOperationExecution> parseTurtleOperationExecution();
    std::unique_ptr<Production> parseProduction();
    std::unique_ptr<Definition> parseOperationOrEvaluation();
    std::unique_ptr<Operation> parseOperation();
    std::unique_ptr<Evaluation> parseEvaluation();
    std::unique_ptr<LiteralString> parseLiteralString();
    std::unique_ptr<TurtleOperation> parseTurtleOperation();
    std::unique_ptr<TurtleOperation> parseTurtleOperationArguments(
            TurtleOperation::Type operation_type, const char *arg_types);
};
