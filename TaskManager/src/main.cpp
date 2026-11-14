// ============================================================
//  Task Manager — CLI to-do tracker in C++17
//  Author: Mahmoud Saleh
// ============================================================
#include "TaskManager.h"
#include <iostream>
#include <limits>
#include <string>

using namespace taskmgr;

static std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string s;
    std::getline(std::cin, s);
    return s;
}

static int readInt(const std::string& prompt) {
    while (true) {
        std::string s = readLine(prompt);
        try { size_t i; int v = std::stoi(s, &i); if (i == s.size()) return v; }
        catch (...) {}
        std::cout << "  ! Enter a number.\n";
    }
}

static Priority readPriority() {
    std::string s = readLine("Priority (L/M/H): ");
    if (!s.empty() && (s[0] == 'H' || s[0] == 'h')) return Priority::HIGH;
    if (!s.empty() && (s[0] == 'M' || s[0] == 'm')) return Priority::MEDIUM;
    return Priority::LOW;
}

static void printTable(const std::vector<Task>& list) {
    if (list.empty()) { std::cout << "  (no tasks)\n"; return; }
    std::cout << std::left << std::setw(5) << "ID"
              << std::setw(5) << ""
              << std::setw(9) << "Prio"
              << std::setw(12) << "Created"
              << "Title\n";
    std::cout << std::string(70, '-') << "\n";
    for (const auto& t : list) {
        std::cout << std::left << std::setw(5) << t.id
                  << std::setw(5) << t.checkBox()
                  << std::setw(9) << priorityName(t.priority)
                  << std::setw(12) << t.created
                  << t.title << "\n";
    }
}

int main() {
    TaskManager mgr("data/tasks.db");
    mgr.load();

    std::cout << "╔══════════════════════════════════════════╗\n";
    std::cout << "║        TASK MANAGER  -  C++17            ║\n";
    std::cout << "╚══════════════════════════════════════════╝\n";

    while (true) {
        std::cout << "\n1. Show all     2. Add task     3. Toggle done\n";
        std::cout << "4. Delete       5. Pending      6. Completed\n";
        std::cout << "7. By priority  0. Exit\n";
        int c = readInt("Choice: ");

        switch (c) {
            case 0: std::cout << "Goodbye.\n"; return 0;
            case 1: std::cout << "\n"; printTable(mgr.all()); break;
            case 2: {
                std::string title = readLine("Title: ");
                Priority p = readPriority();
                try { mgr.add(title, p); std::cout << "  ✓ Added\n"; }
                catch (const std::exception& e) { std::cout << "  ! " << e.what() << "\n"; }
                break;
            }
            case 3: {
                int id = readInt("Task ID: ");
                std::cout << (mgr.toggle(id) ? "  ✓ Toggled\n" : "  ! Not found\n");
                break;
            }
            case 4: {
                int id = readInt("Task ID: ");
                std::cout << (mgr.remove(id) ? "  ✓ Deleted\n" : "  ! Not found\n");
                break;
            }
            case 5: std::cout << "\n"; printTable(mgr.pending()); break;
            case 6: std::cout << "\n"; printTable(mgr.completed()); break;
            case 7: std::cout << "\n"; printTable(mgr.byPriority()); break;
            default: break;
        }
    }
}
