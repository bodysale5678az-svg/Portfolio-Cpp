// ============================================================
//  Calculator — recursive-descent expression evaluator in C++17
//  Author: Mahmoud Saleh
// ============================================================
#include "Parser.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

using namespace calc;

static void banner() {
    std::cout << "╔══════════════════════════════════════════╗\n";
    std::cout << "║     CALCULATOR  -  C++17                 ║\n";
    std::cout << "║     + - * / ^ and parentheses            ║\n";
    std::cout << "╚══════════════════════════════════════════╝\n";
    std::cout << "Type an expression (e.g. 2 + 3 * (4 - 1)).\n";
    std::cout << "Commands:  q  quit   h  help\n\n";
}

static void help() {
    std::cout << "\nSupported:  +   -   *   /   ^   ( )\n";
    std::cout << "Precedence: ^  >  * /  >  + -\n";
    std::cout << "^ is right-associative:  2^3^2 = 2^(3^2) = 512\n";
    std::cout << "\nExamples:\n";
    std::cout << "  2 + 3 * 4        = 14\n";
    std::cout << "  (2 + 3) * 4      = 20\n";
    std::cout << "  2 ^ 3 ^ 2        = 512\n";
    std::cout << "  -(5 + 5)         = -10\n\n";
}

int main() {
    banner();

    std::string line;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) break;

        // trim
        size_t b = line.find_first_not_of(" \t");
        if (b == std::string::npos) continue;
        size_t e = line.find_last_not_of(" \t");
        line = line.substr(b, e - b + 1);

        if (line == "q" || line == "quit" || line == "exit") break;
        if (line == "h" || line == "help") { help(); continue; }

        try {
            Parser parser(line);
            NodePtr tree = parser.parse();

            double result = tree->evaluate();
            std::cout << "  " << tree->toString() << "\n";
            std::cout << "  = " << std::fixed << std::setprecision(10) << result << "\n\n";
        } catch (const std::exception& ex) {
            std::cout << "  ! Error: " << ex.what() << "\n\n";
        }
    }

    std::cout << "Goodbye.\n";
    return 0;
}
