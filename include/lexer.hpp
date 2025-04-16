#pragma once

#include <unordered_map>
#include <string>
#include <iostream>

enum class Token {
    // Keywords
    PRINT,
    
    // Types
    TYPE_INT,
    
    // Literals
    IDENTIFIER,
    INTEGER,
    STRING,

    // Symbols
    ASSIGNMENT,
    SEMICOLON,

    // EOF
    END,

    // Error Tokens
    UNTERMINATED_STRING,
    UNKNOWN
};

struct Lexeme {
    Token token;
    std::string value;
};

class Lexer {
    public:
        explicit Lexer(const std::string& input);
        Lexeme get_next_token();

    private:
        std::string input_;
        size_t pos_;
};

void run_lexer_with_debug(const std::string& text);
