#pragma once
#include <string>
#include <vector>
#include <memory>
#include <cmath>
#include <stdexcept>

namespace calc {

/**
 * Expression tree — demonstrates POLYMORPHISM and COMPOSITION.
 *
 * Every node knows how to evaluate itself and how to print itself,
 * so the evaluator and the printer never need to know node types.
 */
class Node {
public:
    virtual ~Node() = default;
    virtual double evaluate() const = 0;
    virtual std::string toString() const = 0;
};

using NodePtr = std::unique_ptr<Node>;

/** A literal number. */
class NumberNode : public Node {
    double value;
public:
    explicit NumberNode(double v) : value(v) {}
    double evaluate() const override { return value; }
    std::string toString() const override { return std::to_string(value); }
};

/** Binary operator (+ - * / ^). */
class BinaryNode : public Node {
    char op;
    NodePtr left, right;
public:
    BinaryNode(char op, NodePtr l, NodePtr r)
        : op(op), left(std::move(l)), right(std::move(r)) {}

    double evaluate() const override {
        double a = left->evaluate();
        double b = right->evaluate();

        switch (op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/':
                if (b == 0.0) throw std::runtime_error("Division by zero");
                return a / b;
            case '^': return std::pow(a, b);
            default:  throw std::runtime_error(std::string("Unknown operator ") + op);
        }
    }

    std::string toString() const override {
        return "(" + left->toString() + " " + op + " " + right->toString() + ")";
    }
};

/** Unary minus. */
class NegateNode : public Node {
    NodePtr operand;
public:
    explicit NegateNode(NodePtr n) : operand(std::move(n)) {}
    double evaluate() const override { return -operand->evaluate(); }
    std::string toString() const override { return "-" + operand->toString(); }
};

} // namespace calc
