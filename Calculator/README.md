# 🧮 Pocket Calculator — simple C++17

A small, readable calculator that behaves like a real pocket calculator:
a screen, keys, memory and one operation at a time.

```
  ┌─────────────────────────────────┐
  │                                  │
  │                                  │
  │                             56 │
  └─────────────────────────────────┘
   [7] [8] [9]  [/] [C]
   [4] [5] [6]  [x] [CE]
   [1] [2] [3]  [-] [%]
   [0] [.] [=]  [+] [+/-]
   [M+] [M-] [MR] [MC]   [q] quit
```

---

## ✨ Features

- `+  -  ×  ÷` and `=`
- **Chained operations** — `5 + 3 + 2 =` works like a real calculator
- **Percentage** — `50 + 10 %` gives 55
- **Sign flip** — `+/-`
- **Memory** — `M+`, `M-`, `MR`, `MC` with an `M` indicator on screen
- **`C`** clears everything, **`CE`** clears only the current entry
- Division-by-zero is reported instead of crashing

---

## 🎯 Design goal: readability first

This project is deliberately **not** an expression parser. There is no
tokenizer, no precedence table and no syntax tree — those belong to a
different problem and make the code much harder to read.

Everything lives in one small class:

| Member | Purpose |
|---|---|
| `accumulator` | the value on screen |
| `pending` / `pendingOp` | the left-hand value and the waiting operation |
| `entry` | the digits being typed |
| `startNewNumber` | whether the next digit starts a fresh number |
| `memory` | the `M` register |

The whole behaviour is driven by two methods:

```cpp
void apply(Op op);   // commit the current number, remember the operation
double equals();     // resolve the pending operation
```

---

## 🚀 Build & test

```bash
# build
g++ -std=c++17 -O2 -Iinclude src/main.cpp -o calc

# run
./calc
```

### Unit tests (10 checks)

```bash
g++ -std=c++17 -O2 -Iinclude tests/test_calculator.cpp -o test_calc
./test_calc
```

```
  [PASS] 7 * 8 = 56
  [PASS] 2 + 3 = 5
  [PASS] 10 - 4 = 6
  [PASS] 6 / 4 = 1.5
  [PASS] 5 + 3 + 2 = 10
  [PASS] 50 + 10% = 55
  [PASS] 3.14 entry = 3.14
  [PASS] 5 +/- = -5
  [PASS] M+ then MR = 9
  [PASS] 1 / 0 throws = 1

PASSED: 10  FAILED: 0
```

---

## 📚 What it teaches

- Splitting "what the user is typing" (`entry`) from "the value so far" (`accumulator`)
- A tiny state machine: *entering a number* vs *waiting for the next number*
- Why chained operations need the pending result committed early
- Storing state in members instead of juggling parameters

---

## 👤 Author

**Mahmoud Saleh** — [@bodysale5678az-svg](https://github.com/bodysale5678az-svg)
