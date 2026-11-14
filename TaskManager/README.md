# ✅ Task Manager — CLI To-Do Tracker in C++17

A command-line task manager with priorities, completion tracking, filtering, sorting and automatic persistence to disk.

```
ID   Prio     Created     Title
----------------------------------------------------------------------
1    [ ]      HIGH        2026-11-14  Finish C++ project
2    [x]      LOW         2026-11-14  Read about std::filesystem
```

---

## ✨ Features

- ➕ Add tasks with **priority** (Low / Medium / High)
- ✅ Toggle completion (`[ ]` ↔ `[x]`)
- 🗑️ Delete tasks
- 📋 Filter: **all / pending / completed**
- 🔀 Sort **by priority** (stable sort)
- 💾 **Automatic save** to `data/tasks.db` after every change
- 🛡️ Corrupt records are skipped safely on load

---

## 🏗️ Design

| Component | Role |
|---|---|
| `Priority` (enum class) | Type-safe priority levels |
| `Task` (struct) | Data + serialisation + display helpers |
| `TaskManager` | Owns the list, CRUD, filtering, sorting, persistence |

**Concepts demonstrated**
- `enum class` instead of raw ints
- Composition — `TaskManager` owns `std::vector<Task>`
- `std::stable_sort` with a custom comparator
- File I/O with `std::filesystem` and `std::ofstream`
- Defensive parsing (`try/catch` per record)

---

## 🚀 Build & Run

```bash
g++ -std=c++17 -O2 -Iinclude src/main.cpp -o tasks
./tasks
```

CMake:
```bash
cmake -B build && cmake --build build && ./build/tasks
```

---

## 📁 Data format

`data/tasks.db` — one task per line:

```
id|title|PRIORITY|done|created
1|Finish C++ project|HIGH|0|2026-11-14
```

---

## 👤 Author

**Mahmoud Saleh** — [@bodysale5678az-svg](https://github.com/bodysale5678az-svg)
