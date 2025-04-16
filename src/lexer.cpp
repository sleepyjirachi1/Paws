#include "lexer.hpp"

// Lexer constructor
Lexer::Lexer(const std::string& input_) : input_(input_), pos_(0) {}

// Returns the next token
Lexeme Lexer::get_next_token() {
    while (pos_ < input_.size() && std::isspace(input_[pos_])) {
        pos_++; // Ignore whitespace
    }

    if (pos_ >= input_.size()) return {Token::END, ""};

    char current_char = input_[pos_];

    // Syntax
    switch (current_char) {
        case ';':
            pos_++;
            return {Token::SEMICOLON, ";"};
        case '=':
            pos_++;
            return {Token::ASSIGNMENT, "="};
        default:
            break;
    }

    // Strings
    if (current_char == '"') {
        pos_++; // Skip the quotation marks
        std::string literal;
        while (pos_ < input_.size() && input_[pos_] != '"') { 
            literal += input_[pos_++];
        }
        if (pos_ < input_.size() && input_[pos_] == '"') {
            pos_++; // Skip the quotation marks
        } else return {Token::UNTERMINATED_STRING, literal};
        return {Token::STRING, literal};
    }

    // Numbers
    else if (std::isdigit(current_char)) {
        std::string value;
        while (pos_ < input_.size() && std::isdigit(input_[pos_])) {
            value += input_[pos_++];
        }
        return {Token::INTEGER, value};
    }

    // Keywords, identifiers and type specifiers
    else if (std::isalpha(current_char)) {
        std::string value;
        while (pos_ < input_.size() && (std::isalnum(input_[pos_]) || input_[pos_] == '_')) {
            value += input_[pos_++];
        }
        if (value == "print") return {Token::PRINT, value};
        else if (value == "int") return {Token::TYPE_INT, value};
        else return {Token::IDENTIFIER, value};
    }

    return {Token::UNKNOWN, std::string(1, current_char)};
}

// Map to stringify tokens
static const std::unordered_map<Token, std::string> token_to_string_map = {
    {Token::PRINT, "PRINT"},
    {Token::TYPE_INT, "TYPE_INT"},
    {Token::IDENTIFIER, "IDENTIFIER"},
    {Token::INTEGER, "INTEGER"},
    {Token::STRING, "STRING"},
    {Token::ASSIGNMENT, "ASSIGNMENT"},
    {Token::SEMICOLON, "SEMICOLON"},
    {Token::END, "END"},
    {Token::UNTERMINATED_STRING, "UNTERMINATED_STRING"},
    {Token::UNKNOWN, "UNKNOWN"}
};

// Cast a token id to its string representation
static std::string token_to_string(const Lexeme& token) {
    // Unordered map find method returns an iterator object
    auto map_iter = token_to_string_map.find(token.token);
    if (map_iter != token_to_string_map.end()) return map_iter->second;
    return "UNKNOWN";
}

// Used for tracking down internal lexer errors
void run_lexer_with_debug(const std::string& text) {
    Lexer lexer(text);
    Lexeme token;

    while ((token = lexer.get_next_token()).token != Token::END) {
        std::cout << token_to_string(token) << ", Value: " << token.value << std::endl;
    }
}
