#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>

namespace taskmgr {

/** Priority of a task. */
enum class Priority { LOW, MEDIUM, HIGH };

inline std::string priorityName(Priority p) {
    switch (p) {
        case Priority::LOW:    return "LOW";
        case Priority::MEDIUM: return "MEDIUM";
        case Priority::HIGH:   return "HIGH";
    }
    return "LOW";
}

inline Priority priorityFromName(const std::string& s) {
    if (s == "HIGH")   return Priority::HIGH;
    if (s == "MEDIUM") return Priority::MEDIUM;
    return Priority::LOW;
}

/**
 * Task — a single to-do entry.
 * Shows a struct with behaviour, operator overloading and serialisation.
 */
struct Task {
    int         id;
    std::string title;
    Priority    priority;
    bool        done;
    std::string created;

    Task() : id(0), priority(Priority::LOW), done(false) {}

    Task(int id, std::string title, Priority p, std::string created)
        : id(id), title(std::move(title)), priority(p), done(false),
          created(std::move(created)) {}

    /** Persisted as: id|title|priority|done|created */
    std::string toRecord() const {
        return std::to_string(id) + "|" + title + "|" + priorityName(priority) + "|" +
               (done ? "1" : "0") + "|" + created;
    }

    static Task fromRecord(const std::string& line) {
        std::stringstream ss(line);
        std::string sId, title, prio, sDone, created;
        std::getline(ss, sId,    '|');
        std::getline(ss, title,  '|');
        std::getline(ss, prio,   '|');
        std::getline(ss, sDone,  '|');
        std::getline(ss, created,'|');

        Task t(std::stoi(sId), title, priorityFromName(prio), created);
        t.done = (sDone == "1");
        return t;
    }

    /** Display checkbox: [x] or [ ] */
    std::string checkBox() const { return done ? "[x]" : "[ ]"; }
};

/**
 * TaskManager — CRUD plus sorting and filtering over a task list.
 * Composition: owns a vector of tasks and its storage folder.
 */
class TaskManager {
private:
    std::vector<Task> tasks;
    std::filesystem::path file;
    int nextId = 1;

    static std::string now() {
        std::time_t t = std::time(nullptr);
        char buf[20];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d", std::localtime(&t));
        return buf;
    }

public:
    explicit TaskManager(std::filesystem::path path = "data/tasks.db")
        : file(std::move(path)) {}

    const std::vector<Task>& all() const { return tasks; }

    // ---------- CRUD ----------
    Task& add(const std::string& title, Priority p) {
        if (title.empty()) throw std::invalid_argument("Title cannot be empty");
        tasks.emplace_back(nextId++, title, p, now());
        save();
        return tasks.back();
    }

    bool toggle(int id) {
        for (auto& t : tasks) {
            if (t.id == id) { t.done = !t.done; save(); return true; }
        }
        return false;
    }

    bool remove(int id) {
        for (auto it = tasks.begin(); it != tasks.end(); ++it) {
            if (it->id == id) { tasks.erase(it); save(); return true; }
        }
        return false;
    }

    bool setPriority(int id, Priority p) {
        for (auto& t : tasks) {
            if (t.id == id) { t.priority = p; save(); return true; }
        }
        return false;
    }

    // ---------- queries ----------
    std::vector<Task> pending() const {
        std::vector<Task> out;
        for (const auto& t : tasks) if (!t.done) out.push_back(t);
        return out;
    }

    std::vector<Task> completed() const {
        std::vector<Task> out;
        for (const auto& t : tasks) if (t.done) out.push_back(t);
        return out;
    }

    /** Sorted high→low priority (stable). */
    std::vector<Task> byPriority() const {
        std::vector<Task> out = tasks;
        std::stable_sort(out.begin(), out.end(), [](const Task& a, const Task& b) {
            return static_cast<int>(a.priority) > static_cast<int>(b.priority);
        });
        return out;
    }

    // ---------- persistence ----------
    void save() const {
        std::filesystem::create_directories(file.parent_path());
        std::ofstream out(file, std::ios::trunc);
        for (const auto& t : tasks) out << t.toRecord() << '\n';
    }

    void load() {
        tasks.clear();
        nextId = 1;
        std::ifstream in(file);
        std::string line;
        while (std::getline(in, line)) {
            if (!line.empty() && line.back() == '\r') line.pop_back();
            if (line.empty()) continue;
            try {
                Task t = Task::fromRecord(line);
                nextId = std::max(nextId, t.id + 1);
                tasks.push_back(t);
            } catch (...) {}
        }
    }
};

} // namespace taskmgr
