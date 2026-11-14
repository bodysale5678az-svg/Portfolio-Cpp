#pragma once
#include "Node.h"
#include <string>
#include <cctype>

namespace calc {

/**
 * Recursive-descent expression parser.
 *
 * Grammar (by precedence, lowest first):
 *   expression := term   (('+' | '-') term)*
 *   term       := power  (('*' | '/') power)*
 *   power      := unary  ('^' unary)*        -- right associative
 *   unary      := '-' unary | primary
 *   primary    := number | '(' expression ')'
 */
class Parser {
public:
    explicit Parser(std::string input) : src(std::move(input)), pos(0) {}

    NodePtr parse() {
        NodePtr node = expression();
        skipSpaces();
        if (pos != src.size())
            throw std::runtime_error("Unexpected character at position " + std::to_string(pos));
        return node;
    }

private:
    std::string src;
    size_t pos;

    void skipSpaces() {
        while (pos < src.size() && std::isspace((unsigned char)src[pos])) ++pos;
    }

    bool match(char c) {
        skipSpaces();
        if (pos < src.size() && src[pos] == c) { ++pos; return true; }
        return false;
    }

    NodePtr expression() {
        NodePtr node = term();
        while (true) {
            if (match('+'))      node = std::make_unique<BinaryNode>('+', std::move(node), term());
            else if (match('-')) node = std::make_unique<BinaryNode>('-', std::move(node), term());
            else break;
        }
        return node;
    }

    NodePtr term() {
        NodePtr node = power();
        while (true) {
            if (match('*'))      node = std::make_unique<BinaryNode>('*', std::move(node), power());
            else if (match('/')) node = std::make_unique<BinaryNode>('/', std::move(node), power());
            else break;
        }
        return node;
    }

    NodePtr power() {
        NodePtr base = unary();
        if (match('^')) {
            // right-associative: 2^3^2 == 2^(3^2)
            return std::make_unique<BinaryNode>('^', std::move(base), power());
        }
        return base;
    }

    NodePtr unary() {
        if (match('-')) return std::make_unique<NegateNode>(unary());
        if (match('+')) return unary();
        return primary();
    }

    NodePtr primary() {
        skipSpaces();
        if (match('(')) {
            NodePtr inner = expression();
            if (!match(')')) throw std::runtime_error("Missing closing parenthesis");
            return inner;
        }

        skipSpaces();
        size_t start = pos;
        while (pos < src.size() && (std::isdigit((unsigned char)src[pos]) || src[pos] == '.'))
            ++pos;

        if (start == pos) throw std::runtime_error("Expected a number at position " + std::to_string(pos));

        return std::make_unique<NumberNode>(std::stod(src.substr(start, pos - start)));
    }
};

} // namespace calc
