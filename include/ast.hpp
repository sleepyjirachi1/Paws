#pragma once

#include <string>
#include <memory>

struct Statement {
    virtual ~Statement() = default;
};

struct PrintStatement : Statement {
    std::string literal;

    PrintStatement(const std::string& str) : literal(str) {};
};

struct VariableDeclaration : Statement {
    std::string type;
    std::string name;
    std::string value;

    VariableDeclaration(const std::string& t, const std::string& n, const std::string& v)
    : type(t), name(n), value(v) {}
};
