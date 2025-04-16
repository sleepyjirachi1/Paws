#pragma once

#include <vector>
#include <memory>

#include "lexer.hpp"
#include "ast.hpp"

using StatementPtr = std::unique_ptr<Statement>;

class Parser {
    public:
        explicit Parser(Lexer lexer);
        std::vector<StatementPtr> parse();

    private:
        Lexer lexer_;
        Lexeme current_token_;

        void advance();
        bool match(Token token);
        bool expect(Token token, const std::string& errorMsg);

        StatementPtr parseStatement();
        StatementPtr parsePrint();
        StatementPtr parseDeclaration();

        [[noreturn]] void error(const std::string& message);
};
