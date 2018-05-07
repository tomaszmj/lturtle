#include "parser.h"
#include "lexer.h"
#include "exception.h"

using namespace parser;

Parser::Parser(lexer::Lexer &lex)
    : lexer(lex)
{
    nextToken();
}

const lexer::Lexer &Parser::getLexer()
{
    return lexer;
}

std::unique_ptr<Program> Parser::parseProgram()
{
    std::unique_ptr<Program> retval(new Program);
    while(currentToken->getSymbol() != lexer::Token::end_of_text)
    {
        retval->statements.push_back(parseStatementPrivate());
        consume(lexer::Token::semicolon_symbol);
    }
    return std::move(retval);
}

std::unique_ptr<Statement> Parser::parseStatement()
{
    if(currentToken->getSymbol() == lexer::Token::end_of_text)
        return std::unique_ptr<Statement>(nullptr);
    std::unique_ptr<Statement> retval(parseStatementPrivate());
    consume(lexer::Token::semicolon_symbol);
    return std::move(retval);
}

// nextToken() is called each time when currentToken has already been used to make a decision / construct syntax tree element
void Parser::nextToken()
{
    currentToken = lexer.getNextToken();
}

// consume() is called when there is only one expected token, which will NOT be used to construct syntax tree
void Parser::consume(lexer::Token::Symbol token_type)
{
    if(currentToken->getSymbol() != token_type)
        error("expected token " + lexer::Token::typeToString(token_type)); // in this situation parser can 'ignore' the lack of expected token
    nextToken();
}

// accept() is called when there is only one expected token, which WILL be used to construct syntax tree
std::unique_ptr<lexer::Token> Parser::accept(std::initializer_list<lexer::Token::Symbol> token_types)
{
    bool ok = false;
    for(auto token : token_types)
    {
        if(currentToken->getSymbol() == token)
        {
            ok = true;
            break;
        }
    }
    if(!ok)
    {
        std::string msg = "expected token types:";
        for(auto token : token_types)
            msg += " " + lexer::Token::typeToString(token);
        error(std::move(msg)); // in this situation parser can NOT 'ignore' the lack of expected token
    }
    std::unique_ptr<lexer::Token> retval = std::move(currentToken);
    nextToken();
    return std::move(retval);
}

void Parser::error(std::string &&msg)
{
    throw ParserException("at token '" + currentToken->toString() + "' (from " +
        currentToken->getPositionBegin().toString() + " to " +
        currentToken->getPositionEnd().toString() + "): " + msg);
}

std::unique_ptr<Statement> Parser::parseStatementPrivate()
{
    switch(currentToken->getSymbol())
    {
        case lexer::Token::redefine_keyword:
            nextToken();
            return parseRedefinition();
        case lexer::Token::literal:
            return parseDefinition();
        case lexer::Token::execute_keyword:
            nextToken();
            return parseLiteralExecution();
        default:
            return parseTurtleOperationExecution();
    }
}

std::unique_ptr<Definition> Parser::parseRedefinition()
{
    std::unique_ptr<Definition> retval = parseDefinition();
    retval->canRedefine = true;
    return std::move(retval);
}

std::unique_ptr<Definition> Parser::parseDefinition()
{
    std::unique_ptr<Definition> retval;
    std::unique_ptr<lexer::Token> literal = std::move(currentToken); // assign it later, because retval has not been allocated yet
    nextToken();
    if(currentToken->getSymbol() == lexer::Token::production_operator)
    {
        nextToken();
        retval = parseProduction();
    }
    else if(currentToken->getSymbol() == lexer::Token::equals_symbol)
    {
        nextToken();
        retval = parseOperationOrEvaluation();
    }
    else
        error("expected '=' or '->' after literal '" + literal->toString() + "'");
    retval->literal = std::move(literal);
    retval->canRedefine = false;
    return std::move(retval);
}

std::unique_ptr<LiteralExecution> Parser::parseLiteralExecution()
{
    std::unique_ptr<LiteralExecution> retval(new LiteralExecution);
    consume(lexer::Token::l_round_bracket_symbol);
    retval->literals = parseLiteralString();
    consume(lexer::Token::r_round_bracket_symbol);
    return std::move(retval);
}

std::unique_ptr<TurtleOperationExecution> Parser::parseTurtleOperationExecution()
{
    std::unique_ptr<TurtleOperationExecution> retval(new TurtleOperationExecution);
    retval->turtleOperation = parseTurtleOperation();
    return std::move(retval);
}

std::unique_ptr<Production> Parser::parseProduction()
{
    std::unique_ptr<Production> retval(new Production);
    retval->literals = parseLiteralString();
    return std::move(retval);
}

std::unique_ptr<Definition> Parser::parseOperationOrEvaluation()
{
    if(currentToken->getSymbol() == lexer::Token::l_curly_bracket_symbol)
    {
        nextToken();
        return parseOperation();
    }
    else if(currentToken->getSymbol() == lexer::Token::evaluate_keyword)
    {
        nextToken();
        return parseEvaluation();
    }
    error("expected '{' and turtle operations or 'evaluate' and evaluation arguments");
    throw; // unreachable code to suppress compiler warning - function error throws
}

std::unique_ptr<Operation> Parser::parseOperation()
{
    std::unique_ptr<Operation> retval(new Operation);
    while(currentToken->getSymbol() != lexer::Token::r_curly_bracket_symbol)
    {
        retval->turtleOperations.push_back(parseTurtleOperation());
        consume(lexer::Token::semicolon_symbol);
    }
    nextToken(); // r_curly_bracket_symbol consumed
    return std::move(retval);
}

std::unique_ptr<Evaluation> Parser::parseEvaluation()
{
    std::unique_ptr<Evaluation> retval(new Evaluation);
    consume(lexer::Token::l_round_bracket_symbol);
    retval->intNumber = accept({lexer::Token::int_number});
    consume(lexer::Token::colon_symbol);
    retval->literals = parseLiteralString();
    consume(lexer::Token::r_round_bracket_symbol);
    return std::move(retval);
}

std::unique_ptr<LiteralString> Parser::parseLiteralString()
{
    std::unique_ptr<LiteralString> retval(new LiteralString);
    retval->literals.push_back(accept({lexer::Token::literal})); // LiteralString cannot be empty
    while(currentToken->getSymbol() == lexer::Token::plus_symbol)
    {
        nextToken();
        retval->literals.push_back(accept({lexer::Token::literal}));
    }
    return std::move(retval);
}

std::unique_ptr<TurtleOperation> Parser::parseTurtleOperation()
{
    std::unique_ptr<TurtleOperation> retval(new TurtleOperation);
    switch(currentToken->getSymbol())
    {
        case lexer::Token::forward_keyword:
            retval->type = TurtleOperation::forward_operation;
            break;
        case lexer::Token::rotate_keyword:
            retval->type = TurtleOperation::rotate_operation;
            break;
        case lexer::Token::penup_keyword:
            retval->type = TurtleOperation::penup_operation;
            break;
        case lexer::Token::pendown_keyword:
            retval->type = TurtleOperation::pendown_operation;
            break;
        case lexer::Token::pencolour_keyword:
            retval->type = TurtleOperation::pencolour_operation;
            break;
        case lexer::Token::goto_keyword:
            retval->type = TurtleOperation::goto_operation;
            break;
        case lexer::Token::pensize_keyword:
            retval->type = TurtleOperation::pensize_operation;
            break;
        case lexer::Token::scale_keyword:
            retval->type = TurtleOperation::scale_operation;
            break;
        case lexer::Token::pushstate_keyword:
            retval->type = TurtleOperation::pushstate_operation;
            break;
        case lexer::Token::popstate_keyword:
            retval->type = TurtleOperation::popstate_operation;
            break;
        default:
            error("expected one of turtle operation keywords");
    }
    nextToken();
    consume(lexer::Token::l_round_bracket_symbol);
    retval->arguments = parseTurtleOperationArguments();
    consume(lexer::Token::r_round_bracket_symbol);
    return retval;
}

std::unique_ptr<TurtleOperationArguments> Parser::parseTurtleOperationArguments()
{
    std::unique_ptr<TurtleOperationArguments> retval(new TurtleOperationArguments);
    if(currentToken->getSymbol() != lexer::Token::float_number && currentToken->getSymbol() != lexer::Token::int_number)
        return std::move(retval);
    retval->numbers.push_back(std::move(currentToken));
    nextToken();
    while(currentToken->getSymbol() == lexer::Token::colon_symbol)
    {
        nextToken();
        retval->numbers.push_back(accept({lexer::Token::int_number, lexer::Token::float_number}));
    } 
    return std::move(retval);
}
