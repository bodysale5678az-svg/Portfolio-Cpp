// ============================================================
//  Pocket Calculator — simple, readable C++17
//  Author: Mahmoud Saleh
// ============================================================
#include "Calculator.h"
#include <iostream>
#include <string>

using namespace calc;

static void showScreen(const Calculator& c) {
    std::cout << "\n";
    std::cout << "  ┌─────────────────────────────────┐\n";
    std::cout << "  │ " << (c.hasMemory() ? "M " : "  ")
              << std::string(31, ' ') << "│\n";
    std::cout << "  │ " << std::string(31, ' ') << "│\n";
    std::cout << "  │ " << [&] {
        std::string d = c.display();
        if (d.size() > 29) d = d.substr(0, 29);
        return std::string(29 - d.size(), ' ') + d;
    }() << " │\n";
    std::cout << "  └─────────────────────────────────┘\n";
}

static void showKeys() {
    std::cout << "   [7] [8] [9]  [/] [C]\n";
    std::cout << "   [4] [5] [6]  [x] [CE]\n";
    std::cout << "   [1] [2] [3]  [-] [%]\n";
    std::cout << "   [0] [.] [=]  [+] [+/-]\n";
    std::cout << "   [M+] [M-] [MR] [MC]   [q] quit\n";
}

int main() {
    Calculator calc;
    std::cout << "╔═══════════════════════════════════════╗\n";
    std::cout << "║        POCKET CALCULATOR  (C++)       ║\n";
    std::cout << "╚═══════════════════════════════════════╝\n";
    std::cout << "Type a key and press Enter.\n";

    while (true) {
        showScreen(calc);
        showKeys();
        std::cout << "\n> ";

        std::string key;
        if (!std::getline(std::cin, key)) break;

        // trim
        while (!key.empty() && (key.front() == ' ' || key.front() == '\t')) key.erase(0, 1);
        while (!key.empty() && (key.back() == ' ' || key.back() == '\r' || key.back() == '\t')) key.pop_back();
        if (key.empty()) continue;

        try {
            if (key.size() == 1 && key[0] >= '0' && key[0] <= '9') {
                calc.digit(key[0]);
            }
            else if (key == "." || key == ",")      calc.dot();
            else if (key == "+")                    calc.apply(Calculator::Op::Add);
            else if (key == "-")                    calc.apply(Calculator::Op::Subtract);
            else if (key == "*" || key == "x" || key == "X") calc.apply(Calculator::Op::Multiply);
            else if (key == "/")                    calc.apply(Calculator::Op::Divide);
            else if (key == "=")                    calc.equals();
            else if (key == "%")                    calc.percent();
            else if (key == "+/-" || key == "n")    calc.negate();
            else if (key == "c" || key == "C")      calc.clearAll();
            else if (key == "ce" || key == "CE")    calc.clearEntry();
            else if (key == "m+" || key == "M+")    calc.memoryAdd();
            else if (key == "m-" || key == "M-")    calc.memorySubtract();
            else if (key == "mr" || key == "MR")    calc.memoryRecall();
            else if (key == "mc" || key == "MC")    calc.memoryClear();
            else if (key == "q" || key == "quit")   break;
            else if (key == "h" || key == "help") {
                std::cout << "\n  + - * /   arithmetic\n"
                          << "  =         result\n"
                          << "  %         percentage\n"
                          << "  +/-       change sign\n"
                          << "  C         clear all\n"
                          << "  CE        clear entry\n"
                          << "  M+ M- MR MC   memory\n";
                std::cout << "\nPress Enter...";
                std::getline(std::cin, key);
            }
            else {
                std::cout << "  ! Unknown key: " << key << "   (h for help)\n";
                std::cout << "  Press Enter...";
                std::getline(std::cin, key);
            }
        }
        catch (const std::exception& ex) {
            std::cout << "  ! Error: " << ex.what() << "\n";
            std::cout << "  Press Enter...";
            std::getline(std::cin, key);
        }
    }

    std::cout << "\nGoodbye.\n";
    return 0;
}
