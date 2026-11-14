# Portfolio — C++

A collection of small, self-contained C++17 projects that show range:
parsing, algorithms, data structures and file persistence.

| Project | What it demonstrates | Build |
|---|---|---|
| [**Calculator**](Calculator/) | Recursive-descent parser, expression tree, polymorphism | `g++ -std=c++17 -Iinclude src/main.cpp -o calc` |
| [**ProblemSolving**](ProblemSolving/) | 11 classic algorithms + self-testing runner | `g++ -std=c++17 -Iinclude src/main.cpp -o problems` |
| [**TaskManager**](TaskManager/) | CRUD, enums, stable sort, file persistence | `g++ -std=c++17 -Iinclude src/main.cpp -o tasks` |

---

## 🛠️ Requirements

- A C++17 compiler (GCC 9+, Clang 10+, MSVC 2019+)
- No external libraries

## 🚀 Build everything

```bash
# Calculator
cd Calculator && g++ -std=c++17 -O2 -Iinclude src/main.cpp -o calc

# Problem solver (test suite)
cd ProblemSolving && g++ -std=c++17 -O2 -Iinclude src/main.cpp -o problems && ./problems

# Task manager
cd TaskManager && g++ -std=c++17 -O2 -Iinclude src/main.cpp -o tasks
```

---

## 🎯 Focus areas

- **OOP** — abstract classes, inheritance, polymorphism, encapsulation, composition
- **Algorithms** — hashing, two pointers, binary search, stacks, recursion, dynamic programming
- **Modern C++** — `std::unique_ptr`, `enum class`, lambdas, `std::filesystem`, STL algorithms
- **Clean builds** — all projects compile with `-Wall -Wextra` and no warnings

---

## 👤 Author

**Mahmoud Saleh** — [@bodysale5678az-svg](https://github.com/bodysale5678az-svg)
