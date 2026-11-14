#pragma once
#include <string>
#include <sstream>
#include <stdexcept>
#include <cmath>

namespace calc {

/**
 * Calculator — a small, honest calculator.
 *
 * Deliberately simple: two numbers and one operation, plus the few
 * extras a real pocket calculator has — memory, percentage and sign
 * flipping. No expression parser, no operator precedence, no trees.
 *
 * The point of this file is readability: someone reading it for the
 * first time should understand every line.
 */
class Calculator {
public:
    enum class Op { None, Add, Subtract, Multiply, Divide, Percent };

    // ---- state ----
    double accumulator = 0.0;   // value on the display
    double memory      = 0.0;   // M+ / M- storage
    double pending     = 0.0;   // left-hand value waiting for an operation
    Op     pendingOp   = Op::None;
    bool   startNewNumber = true;
    std::string entry;          // digits typed so far

    // ---- display ----
    std::string display() const {
        if (!entry.empty()) return entry;

        // Trim trailing zeros so "3.50" shows as "3.5" and "4.0" as "4"
        std::ostringstream out;
        out.precision(12);
        out << accumulator;
        std::string s = out.str();

        if (s.find('.') != std::string::npos) {
            while (!s.empty() && s.back() == '0') s.pop_back();
            if (!s.empty() && s.back() == '.') s.pop_back();
        }
        return s.empty() ? "0" : s;
    }

    // ---- digit entry ----
    void digit(char d) {
        if (d < '0' || d > '9') throw std::invalid_argument("not a digit");

        if (startNewNumber) {
            entry.clear();
            startNewNumber = false;
        }
        if (d == '0' && entry == "0") return;   // avoid "007"
        entry += d;
    }

    void dot() {
        if (startNewNumber) {
            entry = "0";
            startNewNumber = false;
        }
        if (entry.find('.') == std::string::npos) entry += '.';
    }

    void clearEntry() {
        entry.clear();
        accumulator = 0.0;
        startNewNumber = true;
    }

    void clearAll() {
        accumulator = 0.0;
        pending = 0.0;
        pendingOp = Op::None;
        entry.clear();
        startNewNumber = true;
    }

    // ---- sign / percent ----
    void negate() {
        if (!entry.empty() && entry[0] == '-') entry.erase(0, 1);
        else if (!entry.empty())              entry.insert(0, "-");
        else                                  accumulator = -accumulator;
    }

    /** Converts the current entry to a percentage of the pending value. */
    void percent() {
        double value = currentValue();
        double result = (pendingOp == Op::Add || pendingOp == Op::Subtract)
                            ? pending * value / 100.0
                            : value / 100.0;
        setValue(result);
    }

    // ---- operations ----
    void apply(Op op) {
        // Chained operations: 2 + 3 + computes 2 + 3 first
        if (pendingOp != Op::None && !startNewNumber) {
            double result = compute(pending, currentValue(), pendingOp);
            pending = result;
            accumulator = result;
        } else {
            // First operation: the number on screen becomes the left-hand side
            pending = currentValue();
            accumulator = pending;
        }

        pendingOp = op;
        startNewNumber = true;
        entry.clear();
    }

    /** Applies the pending operation and shows the result. */
    double equals() {
        if (pendingOp == Op::None) {
            startNewNumber = true;
            entry.clear();
            return accumulator;
        }

        double right = currentValue();
        double result = compute(pending, right, pendingOp);

        accumulator = result;
        pending = 0.0;
        pendingOp = Op::None;
        entry.clear();
        startNewNumber = true;
        return result;
    }

    // ---- memory ----
    void memoryAdd()      { memory += currentValue(); }
    void memorySubtract() { memory -= currentValue(); }
    void memoryRecall()   { setValue(memory); }
    void memoryClear()    { memory = 0.0; }
    bool hasMemory() const { return memory != 0.0; }

private:
    double currentValue() const {
        if (!entry.empty()) {
            try { return std::stod(entry); }
            catch (...) { return 0.0; }
        }
        return accumulator;
    }

    void setValue(double v) {
        accumulator = v;
        entry.clear();
        startNewNumber = true;
    }

    static double compute(double a, double b, Op op) {
        switch (op) {
            case Op::Add:      return a + b;
            case Op::Subtract: return a - b;
            case Op::Multiply: return a * b;
            case Op::Divide:
                if (b == 0.0) throw std::runtime_error("Cannot divide by zero");
                return a / b;
            case Op::Percent:  return a * b / 100.0;
            case Op::None:     return b;
        }
        return b;
    }
};

} // namespace calc
