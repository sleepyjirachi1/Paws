#include "parser.hpp"

#include <stdexcept>

// Constructor needs to call advance()
Parser::Parser(Lexer lexer) : lexer_(lexer) {
    advance(); // Get the first token
}

// Simply advances the token
void Parser::advance() {
    current_token_ = lexer_.get_next_token();
}

// Helper method for expect
bool Parser::match(Token token) {
    if (current_token_.token == token) {
        advance();
        return true;
    }
    return false;
}

// Returns true if current token matches the expected token
bool Parser::expect(Token token, const std::string& errorMsg) {
    if (!match(token)) error(errorMsg);
    return true;
}

// Fancy error wrapper for parser errors
[[noreturn]] void Parser::error(const std::string& message) {
    throw std::runtime_error("Parse error: " + message);
}

// Method returns an array of statements for use in the interpreter
std::vector<StatementPtr> Parser::parse() {
    std::vector<StatementPtr> statements;
    while (current_token_.token != Token::END) {
        statements.push_back(parseStatement());
    }
    return statements;
}

// Determines what type of statement to parse
StatementPtr Parser::parseStatement() {
    if (current_token_.token == Token::PRINT) return parsePrint();
    if (current_token_.token == Token::TYPE_INT) return parseDeclaration();
    // Ideally we want to add row and col to Lexeme for accurate error messages here (applies to all further calls of error function)
    error("Unexpected token: " + current_token_.value);
}

// Parses a print statement with error handling
StatementPtr Parser::parsePrint() {
    advance(); // Consume token and move to the string literal

    if (current_token_.token != Token::IDENTIFIER && current_token_.token != Token::STRING) {
        error("Expected an identifier or string literal after 'print' statement");
    }

    std::string literal = current_token_.value;
    advance();
    expect(Token::SEMICOLON, "Expected ';' after print statement");

    // This returns a unique pointer from a constructor!
    return std::make_unique<PrintStatement>(literal);
}

// Parses a declaration with error handling
StatementPtr Parser::parseDeclaration() {
    std::string type = current_token_.value;
    advance(); // Consume type and move to variable name

    if (current_token_.token != Token::IDENTIFIER) {
        error("Expected variable name after type declaration");
    }

    std::string name = current_token_.value;
    advance(); // Consume identifier and move to value
    expect(Token::ASSIGNMENT, "Expected '=' operator in variable declaration");

    // Code is not scalable! Needs to be changed in future
    if (current_token_.token != Token::INTEGER && current_token_.token != Token::STRING) {
        error("Expect literal value after '='");
    }

    std::string value = current_token_.value;
    advance(); // Consume value
    expect(Token::SEMICOLON, "Expected ';' after declaration");

    // This returns a unique pointer from a constructor!
    return std::make_unique<VariableDeclaration>(type, name, value);
}
