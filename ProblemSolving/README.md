# 🧩 Problem Solving — C++17 Algorithm Collection

![C++17](https://img.shields.io/badge/C%2B%2B-17-00599C?style=flat-square&logo=c%2B%2B&logoColor=white)
![Tests](https://img.shields.io/badge/tests-67%20passing-brightgreen?style=flat-square)

A collection of **25 classic algorithm problems** solved in modern C++, each implemented efficiently and covered by a self-contained test runner.

```
==============================================
  PASSED: 67   FAILED: 0
==============================================
```

---

## 📚 Problems

### Arrays & searching
| # | Problem | Technique | Complexity |
|---|---|---|---|
| 1 | Two Sum | Hash map | O(n) |
| 8 | Binary search | Divide & conquer | O(log n) |
| 15 | Max subarray sum | Kadane | O(n) |
| 16 | Move zeros to end | Two pointers | O(n) |
| 17 | Remove duplicates (sorted) | Two pointers | O(n) |
| 22 | Second largest | Single pass | O(n) |
| 23 | Rotate left by k | Triple reverse | O(n) |
| 24 | Missing number | Arithmetic sum | O(n) |

### Strings
| # | Problem | Technique | Complexity |
|---|---|---|---|
| 2 | Palindrome | Two pointers | O(n) |
| 6 | Reverse string | STL iterators | O(n) |
| 7 | Anagram | Frequency array | O(n) |
| 9 | Balanced parentheses | Stack | O(n) |
| 10 | Longest common prefix | Incremental shrink | O(n·m) |
| 13 | Count vowels | Single pass | O(n) |
| 19 | Count words | State flag | O(n) |
| 20 | Capitalize words | State flag | O(n) |
| 25 | Longest word | Stream split | O(n) |

### Math & recursion
| # | Problem | Technique | Complexity |
|---|---|---|---|
| 3 | FizzBuzz | Conditionals | O(n) |
| 4 | Fibonacci (memoised) | DP | O(n) |
| 5 | Factorial | Iteration | O(n) |
| 11 | GCD | Euclid | O(log n) |
| 12 | Fibonacci (iterative) | Rolling values | O(n) |
| 14 | Sum of digits | Modulo loop | O(log n) |
| 18 | Is prime | Trial division | O(√n) |
| 21 | Power | Fast exponentiation | O(log n) |

---

## 🏗️ Design

All problems live as **static functions** in the `Algorithms` class
(`include/Algorithms.h`) — no object state needed, so they stay pure and
easy to test.

A small hand-written test runner in `src/main.cpp` checks every function
against expected values, prints a pass/fail summary, and returns a non-zero
exit code on failure (CI-friendly).

---

## 🚀 Build & run

```bash
g++ -std=c++17 -O2 -Iinclude src/main.cpp -o problems
./problems
```

Sample output:
```
--- 18. Is prime ---
  [PASS] 2
  [PASS] 97
  [PASS] 1
  [PASS] 100

==============================================
  PASSED: 67   FAILED: 0
==============================================
```

---

## 💡 Why this repo exists

To practise translating problem statements into clean, tested C++ — the
same skills used in coding interviews and technical assessments.

---

## 👤 Author

**Mahmoud Saleh** — [@bodysale5678az-svg](https://github.com/bodysale5678az-svg)
