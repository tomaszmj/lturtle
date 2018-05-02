#include "parser.h"
#include "exception.h"

Parser::Parser(Lexer &lex)
    : lexer(lex)
{
    nextToken();
}

const Lexer &Parser::getLexer()
{
    return lexer;
}

std::unique_ptr<Program> Parser::parseProgram()
{
    std::unique_ptr<Program> program;
    while(t->getSymbol() != Token::end_of_text)
    {
        program->statements.push_back(parseStatement());
        consume(Token::semicolon_symbol);
    }
    return std::move(program);
}

void Parser::nextToken()
{
    t = lexer.getNextToken();
}

void Parser::consume(Token::Symbol token_type)
{
    if(t->getSymbol() != token_type)
        throw Exception("Unexpected token... TODO\n"); // in this situation parser can 'ignore' the lack of expected token
    nextToken();
}


std::unique_ptr<Statement> Parser::parseStatement()
{

}

std::unique_ptr<Statement> Parser::parseRedefinition()
{

}

std::unique_ptr<Statement> Parser::parseDefinition()
{

}

std::unique_ptr<Statement> Parser::parseLiteralExecution()
{

}

std::unique_ptr<Statement> Parser::parseTurtleOperationExecution()
{

}

std::unique_ptr<Statement> Parser::parseProduction()
{

}

std::unique_ptr<Statement> Parser::parseOperationOrEvaluation()
{

}

std::unique_ptr<Statement> Parser::parseOperation()
{

}

std::unique_ptr<Statement> Parser::parseEvaluation()
{

}

std::unique_ptr<LiteralString> Parser::parseLiteralString()
{

}

std::unique_ptr<TurtleOperation> Parser::parseTurtleOperation()
{

}
