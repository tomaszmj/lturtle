#pragma once
#include "syntax_tree.h"
#include "token.h"
#include <memory>
#include <initializer_list>

class Lexer;

class Parser
{
public:
    Parser(Lexer &lex);
    const Lexer &getLexer();

    // returns the whole 'syntax tree', with root node - Program
    // returned value is always not null, however Program can contain no statements
    std::unique_ptr<Program> parseProgram();

    // parseStatement allows to 'parseProgram' statement by statement, without saving each statement in memory
    // returned value can be nullptr if end of text was encountered
    std::unique_ptr<Statement> parseStatement();

private:
    Lexer &lexer;
    std::unique_ptr<Token> currentToken;

    void nextToken();
    void consume(Token::Symbol token_type);

    std::unique_ptr<Token> accept(std::initializer_list<Token::Symbol> token_types);
    void error(std::string &&msg);

    std::unique_ptr<Statement> parseStatementPrivate();
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
    std::unique_ptr<TurtleOperationArguments> parseTurtleOperationArguments();
};
