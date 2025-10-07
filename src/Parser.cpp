#include "Parser.h"
#include <stdexcept>
#include <iostream>

using namespace Mini;

bool Parser::match(TokenType type)
{
    if (check(type))
    {
        advance();
        return true;
    }
    return false;
}

bool Parser::check(TokenType type) const
{
    if (isAtEnd())
        return false;
    return peek().type == type;
}

bool Parser::isAtEnd() const
{
    return peek().type == TokenType::End;
}

Token Parser::advance()
{
    if (!isAtEnd())
        current++;
    return previous();
}

Token Parser::peek() const
{
    return tokens[current];
}

Token Parser::previous() const
{
    return tokens[current - 1];
}

Token Parser::consume(TokenType type, const std::string &msg)
{
    if (check(type))
        return advance();
    throw std::runtime_error("Error[" + std::to_string(peek().line) + ":" + std::to_string(peek().col) + "]: " + msg);
}

std::unique_ptr<Expr> Parser::parsePrimary()
{
    if (match(TokenType::Number))
    {
        return std::make_unique<NumberExpr>(std::stoi(previous().text));
    }
    if (match(TokenType::Identifier))
    {
        return std::make_unique<VarExpr>(previous().text);
    }
    if (match(TokenType::LParen))
    {
        auto expr = parseExpression();
        consume(TokenType::RParen, "expected ')'");
        return expr;
    }
    throw std::runtime_error("Unexpected token in primary expression");
}

std::unique_ptr<Expr> Parser::parseExpression()
{
    return parseComparison();
}

std::unique_ptr<Expr> Parser::parseComparison()
{
    auto expr = parseTerm();
    while (match(TokenType::Less))
    {
        auto rhs = parseTerm();
        expr = std::make_unique<BinaryExpr>(BinaryExpr::Op::Lt, std::move(expr), std::move(rhs));
    }
    return expr;
}

std::unique_ptr<Expr> Parser::parseTerm()
{
    auto expr = parseFactor();
    while (match(TokenType::Plus) || match(TokenType::Minus))
    {
        BinaryExpr::Op op = (previous().type == TokenType::Plus) ? BinaryExpr::Op::Add : BinaryExpr::Op::Sub;
        auto rhs = parseFactor();
        expr = std::make_unique<BinaryExpr>(op, std::move(expr), std::move(rhs));
    }
    return expr;
}

std::unique_ptr<Expr> Parser::parseFactor()
{
    auto expr = parsePrimary();
    while (match(TokenType::Star) || match(TokenType::Slash))
    {
        BinaryExpr::Op op = (previous().type == TokenType::Star) ? BinaryExpr::Op::Mul : BinaryExpr::Op::Div;
        auto rhs = parsePrimary();
        expr = std::make_unique<BinaryExpr>(op, std::move(expr), std::move(rhs));
    }
    return expr;
}

std::unique_ptr<Stmt> Parser::parseStatement()
{
    if (match(TokenType::Let))
    {
        auto name = consume(TokenType::Identifier, "expected identifier").text;
        consume(TokenType::Equal, "expected '='");
        auto init = parseExpression();
        consume(TokenType::Semicolon, "expected ';'");
        return std::make_unique<LetStmt>(name, std::move(init));
    }

    if (match(TokenType::Identifier))
    {
        std::string name = previous().text;
        consume(TokenType::Equal, "expected '='");
        auto val = parseExpression();
        consume(TokenType::Semicolon, "expected ';'");
        return std::make_unique<AssignStmt>(name, std::move(val));
    }

    if (match(TokenType::Print))
    {
        consume(TokenType::LParen, "expected '('");
        auto expr = parseExpression();
        consume(TokenType::RParen, "expected ')'");
        consume(TokenType::Semicolon, "expected ';'");
        return std::make_unique<PrintStmt>(std::move(expr));
    }

    if (match(TokenType::While))
    {
        consume(TokenType::LParen, "expected '(' after 'while'");
        auto cond = parseExpression();
        consume(TokenType::RParen, "expected ')' after condition");
        auto body = parseStatement();
        return std::make_unique<WhileStmt>(std::move(cond), std::move(body));
    }

    if (match(TokenType::LBrace))
    {
        auto block = std::make_unique<BlockStmt>();
        while (!check(TokenType::RBrace) && !isAtEnd())
        {
            block->statements.push_back(parseStatement());
        }
        consume(TokenType::RBrace, "expected '}'");
        return block;
    }

    throw std::runtime_error("Unexpected token in statement");
}

std::unique_ptr<Program> Parser::parseProgram()
{
    auto prog = std::make_unique<Program>();
    while (!isAtEnd())
    {
        prog->statements.push_back(parseStatement());
    }
    return prog;
}
