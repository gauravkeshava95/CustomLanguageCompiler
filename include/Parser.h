#pragma once
#include "Lexer.h"
#include "AST.h"
#include <memory>

namespace Mini
{

    class Parser
    {
        const std::vector<Token> &tokens;
        size_t current = 0;

    public:
        Parser(const std::vector<Token> &t) : tokens(t) {}
        std::unique_ptr<Program> parseProgram();

    private:
        std::unique_ptr<Stmt> parseStatement();
        std::unique_ptr<Expr> parseExpression();
        std::unique_ptr<Expr> parseComparison();
        std::unique_ptr<Expr> parseTerm();
        std::unique_ptr<Expr> parseFactor();
        std::unique_ptr<Expr> parsePrimary();

        bool match(TokenType type);
        bool check(TokenType type) const;
        bool isAtEnd() const;
        Token advance();
        Token peek() const;
        Token previous() const;
        Token consume(TokenType type, const std::string &msg);
    };

} // namespace Mini
