#pragma once
#include <string>
#include <vector>

namespace Mini
{

    enum class TokenType
    {
        End,
        Number,
        Identifier,
        Let,
        Print,
        While,
        LParen,
        RParen,
        LBrace,
        RBrace,
        Semicolon,
        Equal,
        Plus,
        Minus,
        Star,
        Slash,
        Less
    };

    struct Token
    {
        TokenType type;
        std::string text;
        int line;
        int col;
    };

    class Lexer
    {
        const std::string &src;
        size_t pos = 0;
        int line = 1, col = 1;

    public:
        Lexer(const std::string &s) : src(s) {}
        std::vector<Token> tokenize();

    private:
        char peek() const;
        char advance();
        bool match(char expected);
        void skipWhitespace();
        Token identifier();
        Token number();
    };

} // namespace Mini
