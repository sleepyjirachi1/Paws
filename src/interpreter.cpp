#include "interpreter.hpp"

#include "lexer.hpp"
#include "parser.hpp"
#include "util.hpp"

// Calling this function will run the interpreter!
void Interpreter::interpret(const std::vector<StatementPtr>& statements) {
    for (const auto& stmt : statements) execute_statement(stmt);
}

// Determine what type of statement we are executing
void Interpreter::execute_statement(const StatementPtr& stmt) {
    if (auto print_stmt = dynamic_cast<PrintStatement*>(stmt.get())) {
        execute_print(print_stmt);
    }
    else if (auto var_decl = dynamic_cast<VariableDeclaration*>(stmt.get())) {
        execute_variable_decl(var_decl);
    }
}

// Standard print functionality, needs to support format strings later
void Interpreter::execute_print(const PrintStatement* stmt) {
    if (variables_.count(stmt->literal)) {
        std::cout << variables_[stmt->literal] << std::endl;
    } 
    else {
        std::cout << stmt->literal << std::endl;
    }
}

// Assign variables to an unordered map
void Interpreter::execute_variable_decl(const VariableDeclaration* stmt) {
    variables_[stmt->name] = stmt->value;
}

// Code should always be run through this!
void exec (const std::string& code) {
    try {
        Lexer lexer(code);
        Parser parser(lexer);

        auto statements = parser.parse();

        Interpreter interpreter;
        interpreter.interpret(statements);
    }
    catch (const std::runtime_error& error) {
        handle_error(error.what());
    }
}
