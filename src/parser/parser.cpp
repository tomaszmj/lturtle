#include "parser.h"
#include "lexer.h"
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
    std::unique_ptr<Program> retval(new Program);
    while(currentToken->getSymbol() != Token::end_of_text)
    {
        retval->statements.push_back(parseStatement());
        consume(Token::semicolon_symbol);
    }
    return std::move(retval);
}

// nextToken() is called each time when currentToken has already been used to make a decision / construct syntax tree element
void Parser::nextToken()
{
    currentToken = lexer.getNextToken();
}

// consume() is called when there is only one expected token, which will NOT be used to construct syntax tree
void Parser::consume(Token::Symbol token_type)
{
    if(currentToken->getSymbol() != token_type)
        error("expected token " + Token::typeToString(token_type)); // in this situation parser can 'ignore' the lack of expected token
    nextToken();
}

// accept() is called when there is only one expected token, which WILL be used to construct syntax tree
std::unique_ptr<Token> Parser::accept(Token::Symbol token_type)
{
    if(currentToken->getSymbol() != token_type)
        error("expected token " + Token::typeToString(token_type)); // in this situation parser can NOT 'ignore' the lack of expected token
    std::unique_ptr<Token> retval = std::move(currentToken);
    nextToken();
    return std::move(retval);
}

void Parser::error(std::string &&msg)
{
    throw ParserException("at token '" + currentToken->toString() + "' (from " +
        currentToken->getPositionBegin().toString() + " to " +
        currentToken->getPositionEnd().toString() + "): " + msg);
}


std::unique_ptr<Statement> Parser::parseStatement()
{
    switch(currentToken->getSymbol())
    {
        case Token::redefine_keyword:
            nextToken();
            return parseRedefinition();
        case Token::literal:
            return parseDefinition();
        case Token::execute_keyword:
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
    std::unique_ptr<Token> literal = std::move(currentToken); // assign it later, because retval has not been allocated yet
    nextToken();
    if(currentToken->getSymbol() == Token::production_operator)
    {
        nextToken();
        retval = parseProduction();
    }
    else if(currentToken->getSymbol() == Token::equals_symbol)
    {
        nextToken();
        retval = parseOperationOrEvaluation();
    }
    else
        error("expected '=' or '->' after literal in definition");
    retval->literal = std::move(literal);
    retval->canRedefine = false;
    return std::move(retval);
}

std::unique_ptr<LiteralExecution> Parser::parseLiteralExecution()
{
    std::unique_ptr<LiteralExecution> retval(new LiteralExecution);
    consume(Token::l_round_bracket_symbol);
    retval->literals = parseLiteralString();
    consume(Token::r_round_bracket_symbol);
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
    if(currentToken->getSymbol() == Token::l_curly_bracket_symbol)
    {
        nextToken();
        return parseOperation();
    }
    else if(currentToken->getSymbol() == Token::evaluate_keyword)
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
    while(currentToken->getSymbol() != Token::r_curly_bracket_symbol)
    {
        retval->turtleOperations.push_back(parseTurtleOperation());
        consume(Token::semicolon_symbol);
    }
    return std::move(retval);
}

std::unique_ptr<Evaluation> Parser::parseEvaluation()
{
    std::unique_ptr<Evaluation> retval(new Evaluation);
    consume(Token::l_round_bracket_symbol);
    retval->intNumber = accept(Token::int_number);
    consume(Token::colon_symbol);
    retval->literals = parseLiteralString();
    consume(Token::l_round_bracket_symbol);
    return std::move(retval);
}

std::unique_ptr<LiteralString> Parser::parseLiteralString()
{
    std::unique_ptr<LiteralString> retval(new LiteralString);
    retval->literals.push_back(accept(Token::literal)); // LiteralString cannot be empty
    while(currentToken->getSymbol() == Token::plus_symbol)
    {
        nextToken();
        retval->literals.push_back(accept(Token::literal));
    }
    return std::move(retval);
}

std::unique_ptr<TurtleOperation> Parser::parseTurtleOperation()
{
    std::unique_ptr<Token> tmp_token = std::move(currentToken);
    nextToken();
    switch(tmp_token->getSymbol())
    {
        case Token::forward_keyword:
            return parseTurtleOperationArguments(TurtleOperation::forward_operation, "f");
        case Token::rotate_keyword:
            return parseTurtleOperationArguments(TurtleOperation::rotate_operation, "f");
        case Token::penup_keyword:
            return parseTurtleOperationArguments(TurtleOperation::penup_operation, "");
        case Token::pendown_keyword:
            return parseTurtleOperationArguments(TurtleOperation::pendown_operation, "");
        case Token::pencolour_keyword:
            return parseTurtleOperationArguments(TurtleOperation::pencolour_operation, "iii");
        case Token::goto_keyword:
            return parseTurtleOperationArguments(TurtleOperation::goto_operation, "ff");
        case Token::pensize_keyword:
            return parseTurtleOperationArguments(TurtleOperation::pensize_operation, "f");
        case Token::scale_keyword:
            return parseTurtleOperationArguments(TurtleOperation::scale_operation, "f");
        case Token::pushstate_keyword:
            return parseTurtleOperationArguments(TurtleOperation::pushstate_operation, "");
        case Token::popstate_keyword:
            return parseTurtleOperationArguments(TurtleOperation::popstate_operation, "");
        default:
            error("expected one of turtle operation keywords");
    }
    throw; // unreachable code to suppress compiler warning - function error throws
}

std::unique_ptr<TurtleOperation> Parser::parseTurtleOperationArguments(
        TurtleOperation::Type operation_type, const char *arg_types)
{
    std::unique_ptr<TurtleOperation> retval(new TurtleOperation);
    retval->type = operation_type;
    consume(Token::l_round_bracket_symbol);
    for(int i = 0; arg_types[i] != 0; ++i) // arg_types is null-terminated string
    {
        if(arg_types[i] == 'f')
            retval->arguments[i] = accept(Token::float_number); // retval->arguments[i] will not overflow because i<=2
        else // arg_types[i] == 'i'
            retval->arguments[i] = accept(Token::int_number);
        if(arg_types[i+1] != 0)
            consume(Token::colon_symbol);
    }
    consume(Token::r_round_bracket_symbol);
    return std::move(retval);
}
