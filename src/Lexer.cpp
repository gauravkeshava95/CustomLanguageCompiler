#include "Lexer.h"
#include <cctype>
#include <stdexcept>

using namespace Mini;

char Lexer::peek() const
{
    return pos < src.size() ? src[pos] : '\0';
}

char Lexer::advance()
{
    char c = peek();
    if (c == '\n')
    {
        line++;
        col = 1;
    }
    else
    {
        col++;
    }
    pos++;
    return c;
}

bool Lexer::match(char expected)
{
    if (peek() == expected)
    {
        advance();
        return true;
    }
    return false;
}

void Lexer::skipWhitespace()
{
    while (isspace(peek()))
        advance();
}

Token Lexer::identifier()
{
    size_t start = pos;
    while (isalnum(peek()) || peek() == '_')
        advance();
    std::string text = src.substr(start, pos - start);
    TokenType type = TokenType::Identifier;
    if (text == "let")
        type = TokenType::Let;
    else if (text == "print")
        type = TokenType::Print;
    else if (text == "while")
        type = TokenType::While;
    return {type, text, line, col};
}

Token Lexer::number()
{
    size_t start = pos;
    while (isdigit(peek()))
        advance();
    return {TokenType::Number, src.substr(start, pos - start), line, col};
}

std::vector<Token> Lexer::tokenize()
{
    std::vector<Token> tokens;
    while (true)
    {
        skipWhitespace();
        char c = peek();
        if (c == '\0')
        {
            tokens.push_back({TokenType::End, "", line, col});
            break;
        }
        if (isalpha(c))
        {
            tokens.push_back(identifier());
            continue;
        }
        if (isdigit(c))
        {
            tokens.push_back(number());
            continue;
        }
        switch (c)
        {
        case '(':
            tokens.push_back({TokenType::LParen, "(", line, col});
            advance();
            break;
        case ')':
            tokens.push_back({TokenType::RParen, ")", line, col});
            advance();
            break;
        case '{':
            tokens.push_back({TokenType::LBrace, "{", line, col});
            advance();
            break;
        case '}':
            tokens.push_back({TokenType::RBrace, "}", line, col});
            advance();
            break;
        case ';':
            tokens.push_back({TokenType::Semicolon, ";", line, col});
            advance();
            break;
        case '=':
            tokens.push_back({TokenType::Equal, "=", line, col});
            advance();
            break;
        case '+':
            tokens.push_back({TokenType::Plus, "+", line, col});
            advance();
            break;
        case '-':
            tokens.push_back({TokenType::Minus, "-", line, col});
            advance();
            break;
        case '*':
            tokens.push_back({TokenType::Star, "*", line, col});
            advance();
            break;
        case '/':
            tokens.push_back({TokenType::Slash, "/", line, col});
            advance();
            break;
        case '<':
            tokens.push_back({TokenType::Less, "<", line, col});
            advance();
            break;
        default:
            throw std::runtime_error("Unexpected character: " + std::string(1, c));
        }
    }
    return tokens;
}
