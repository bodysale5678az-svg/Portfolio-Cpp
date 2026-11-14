# 🧮 Calculator — Recursive Descent Parser in C++17

A command-line calculator that parses and evaluates **arbitrary arithmetic expressions** — not just `a op b`, but full expressions with operator precedence and parentheses.

```
> 2 + 3 * (4 - 1)
  ((2.000000 + (3.000000 * (4.000000 - 1.000000))))
  = 11.0000000000
```

---

## ✨ Features

- Full arithmetic: `+ - * / ^`
- **Parentheses** with arbitrary nesting
- **Correct operator precedence**: `^` > `* /` > `+ -`
- **Right-associative power**: `2^3^2 = 512`
- **Unary minus**: `-(5 + 5) = -10`
- Decimal numbers
- Clear error messages with position info
- Division-by-zero protection

---

## 🏗️ How it works

The parser is a classic **recursive-descent parser** that builds an **expression tree**:

```
Grammar:
  expression := term   (('+' | '-') term)*
  term       := power  (('*' | '/') power)*
  power      := unary  ('^' unary)*          -- right-associative
  unary      := '-' unary | primary
  primary    := number | '(' expression ')'
```

The tree (`2 + 3 * 4`):

```
        +
       / \
      2   *
         / \
        3   4
```

Evaluation happens bottom-up through virtual `evaluate()` calls.

### OOP design

| Class | Responsibility |
|---|---|
| `Node` | Abstract base — `evaluate()` and `toString()` are pure virtual |
| `NumberNode` | A literal value |
| `BinaryNode` | `+ - * / ^` with two children |
| `NegateNode` | Unary minus |
| `Parser` | Turns text into a `NodePtr` tree |

**Polymorphism in action:** `evaluate()` is called on the root node only — each node recurses into its children automatically. The evaluator never checks node types.

---

## 🚀 Build & Run

```bash
g++ -std=c++17 -O2 -Iinclude src/main.cpp -o calculator
./calculator
```

Or with CMake:
```bash
cmake -B build && cmake --build build && ./build/calculator
```

---

## 💡 Examples

| Input | Result |
|---|---|
| `2 + 3 * 4` | 14 |
| `(2 + 3) * 4` | 20 |
| `2 ^ 3 ^ 2` | 512 |
| `-(5 + 5)` | -10 |
| `10 / 4` | 2.5 |
| `1 / 0` | error: Division by zero |

---

## 👤 Author

**Mahmoud Saleh** — [@bodysale5678az-svg](https://github.com/bodysale5678az-svg)
