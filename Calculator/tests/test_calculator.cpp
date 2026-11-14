// Quick sanity check for Calculator (not part of the build)
#include "Calculator.h"
#include <iostream>
#include <string>

using namespace calc;

static int passed = 0, failed = 0;

static void check(const std::string& name, double actual, double expected) {
    bool ok = std::fabs(actual - expected) < 1e-9;
    if (ok) { ++passed; std::cout << "  [PASS] " << name << " = " << actual << "\n"; }
    else    { ++failed; std::cout << "  [FAIL] " << name << " got " << actual
                                  << " expected " << expected << "\n"; }
}

int main() {
    {
        Calculator c;
        c.digit('7'); c.apply(Calculator::Op::Multiply); c.digit('8');
        check("7 * 8", c.equals(), 56);
    }
    {
        Calculator c;
        c.digit('2'); c.apply(Calculator::Op::Add); c.digit('3');
        check("2 + 3", c.equals(), 5);
    }
    {
        Calculator c;
        c.digit('1'); c.digit('0'); c.apply(Calculator::Op::Subtract); c.digit('4');
        check("10 - 4", c.equals(), 6);
    }
    {
        Calculator c;
        c.digit('6'); c.apply(Calculator::Op::Divide); c.digit('4');
        check("6 / 4", c.equals(), 1.5);
    }
    {
        // 5 + 3 + 2 → chained, should compute 8 then wait; = adds 2 → 10
        Calculator c;
        c.digit('5'); c.apply(Calculator::Op::Add);
        c.digit('3'); c.apply(Calculator::Op::Add);
        c.digit('2');
        check("5 + 3 + 2", c.equals(), 10);
    }
    {
        // 50 + 10% → percent of 50 = 5, so 50 + 5 = 55
        Calculator c;
        c.digit('5'); c.digit('0'); c.apply(Calculator::Op::Add);
        c.digit('1'); c.digit('0'); c.percent();
        check("50 + 10%", c.equals(), 55);
    }
    {
        Calculator c;
        c.digit('3'); c.dot(); c.digit('1'); c.digit('4');
        check("3.14 entry", std::stod(c.display()), 3.14);
    }
    {
        Calculator c;
        c.digit('5'); c.negate();
        check("5 +/-", std::stod(c.display()), -5);
    }
    {
        Calculator c;
        c.digit('9'); c.memoryAdd();
        c.clearAll();
        c.memoryRecall();
        check("M+ then MR", std::stod(c.display()), 9);
    }
    {
        Calculator c;
        c.digit('1'); c.apply(Calculator::Op::Divide); c.digit('0');
        bool threw = false;
        try { c.equals(); } catch (...) { threw = true; }
        check("1 / 0 throws", threw ? 1 : 0, 1);
    }

    std::cout << "\nPASSED: " << passed << "  FAILED: " << failed << "\n";
    return failed == 0 ? 0 : 1;
}
