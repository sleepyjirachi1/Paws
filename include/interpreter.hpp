#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>

#include "ast.hpp"

using StatementPtr = std::unique_ptr<Statement>;

class Interpreter {
    public:
        void interpret(const std::vector<StatementPtr>& statements);

    private:
        std::unordered_map<std::string, std::string> variables_;

        void execute_statement(const StatementPtr& stmt);
        void execute_print(const PrintStatement* stmt);
        void execute_variable_decl(const VariableDeclaration* stmt);
};

void exec(const std::string& code);
