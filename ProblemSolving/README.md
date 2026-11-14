# 🧩 Problem Solving — C++17 Algorithm Collection

![C++17](https://img.shields.io/badge/C%2B%2B-17-00599C?style=flat-square&logo=c%2B%2B&logoColor=white)
![CI](https://github.com/bodysale5678az-svg/Portfolio-Cpp/actions/workflows/ci.yml/badge.svg)
![Tests](https://img.shields.io/badge/tests-32%20passing-brightgreen?style=flat-square)

A collection of **11 classic algorithm problems** solved in modern C++, each implemented efficiently and covered by a self-contained test runner.

```
==============================================
  PASSED: 31   FAILED: 0
==============================================
```

---

## 📚 Problems included

| # | Problem | Technique | Complexity |
|---|---|---|---|
| 1 | **Two Sum** | Hash map | O(n) |
| 2 | **Palindrome check** | Two pointers | O(n) |
| 3 | **FizzBuzz** | Conditionals | O(n) |
| 4 | **Fibonacci** | Memoisation | O(n) |
| 5 | **Factorial** | Iteration | O(n) |
| 6 | **Reverse string** | STL iterators | O(n) |
| 7 | **Anagram check** | Frequency array | O(n) |
| 8 | **Binary search** | Divide & conquer | O(log n) |
| 9 | **Balanced parentheses** | Stack | O(n) |
| 10 | **Longest common prefix** | Incremental shrink | O(n·m) |
| 11 | **GCD** | Euclid's algorithm | O(log n) |

---

## 🏗️ Design

All problems live as **static functions** in the `Algorithms` class (`include/Algorithms.h`) — no object state needed, so they stay pure and easy to test.

A small hand-written test runner in `src/main.cpp` checks every function against expected values and prints a pass/fail summary, returning a non-zero exit code on failure (CI-friendly).

---

## 🚀 Build & Run

```bash
g++ -std=c++17 -O2 -Iinclude src/main.cpp -o problems
./problems
```

Sample output:
```
--- 8. Binary search ---
  [PASS] search 7 in sorted [1,3,5,7,9]
  [PASS] search 1 (first)
  [PASS] search 100 (missing)

==============================================
  PASSED: 31   FAILED: 0
==============================================
```

---

## 💡 Why this repo exists

To practise translating problem statements into clean, tested C++ — the same skills used in coding interviews and technical assessments.

---

## 👤 Author

**Mahmoud Saleh** — [@bodysale5678az-svg](https://github.com/bodysale5678az-svg)
