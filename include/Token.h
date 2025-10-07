#pragma once
#include <string>

namespace Mini
{

    enum class TokenType
    {
        // Single-character
        Plus,
        Minus,
        Star,
        Slash,
        Equal,
        Semicolon,
        LParen,
        RParen,
        LBrace,
        RBrace,

        // Literals & identifiers
        Number,
        Identifier,

        // Keywords
        Let,
        Print,
        While,

        // Comparison operators
        Less,         // <
        Greater,      // >
        LessEqual,    // <=
        GreaterEqual, // >=
        EqualEqual,   // ==
        BangEqual,    // !=

        // Special
        End,
        Invalid
    };

    struct SourcePos
    {
        int line{1};
        int col{1};
    };

    struct Token
    {
        TokenType type{TokenType::Invalid};
        std::string lexeme;
        SourcePos pos{};
    };

    inline const char *toString(TokenType t)
    {
        switch (t)
        {
        case TokenType::Plus:
            return "Plus";
        case TokenType::Minus:
            return "Minus";
        case TokenType::Star:
            return "Star";
        case TokenType::Slash:
            return "Slash";
        case TokenType::Equal:
            return "Equal";
        case TokenType::Semicolon:
            return "Semicolon";
        case TokenType::LParen:
            return "LParen";
        case TokenType::RParen:
            return "RParen";
        case TokenType::LBrace:
            return "LBrace";
        case TokenType::RBrace:
            return "RBrace";
        case TokenType::Number:
            return "Number";
        case TokenType::Identifier:
            return "Identifier";
        case TokenType::Let:
            return "Let";
        case TokenType::Print:
            return "Print";
        case TokenType::While:
            return "While";
        case TokenType::Less:
            return "Less";
        case TokenType::Greater:
            return "Greater";
        case TokenType::LessEqual:
            return "LessEqual";
        case TokenType::GreaterEqual:
            return "GreaterEqual";
        case TokenType::EqualEqual:
            return "EqualEqual";
        case TokenType::BangEqual:
            return "BangEqual";
        case TokenType::End:
            return "End";
        default:
            return "Invalid";
        }
    }

} // namespace Mini
