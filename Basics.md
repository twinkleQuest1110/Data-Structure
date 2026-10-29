# 📘 01 - C++ Basics (Logic Building)
 
> Only the core code concepts that build problem-solving logic.
 
## 📑 Table of Contents
1. [Variables](#1-variables)
2. [Data Types](#2-data-types)
3. [Type Conversion (Implicit & Explicit)](#3-type-conversion-implicit--explicit)
---
 
## 1. Variables
 
### 💡 Concept
A variable is a named box in memory that stores a value. You declare it with a type, give it a name, and optionally initialize it.
 
### 💻 Code
```cpp
#include <iostream>
using namespace std;
 
int main() {
    int age = 20;               // declaration + initialization
    int x, y;                   // declaration only (garbage value until assigned)
    x = 10;                     // assignment
    y = x;                      // copy the value of x into y
 
    const double PI = 3.14159;  // constant: cannot be changed
    // PI = 3;                  // ERROR
 
    int a = 5, b = 7;           // multiple variables in one line
    cout << age << " " << x << " " << y << " " << a + b << endl;
    return 0;
}
```
 
### 🔍 Dry Run
 
| Statement | age | x | y |
|-----------|-----|---|---|
| `int age = 20` | 20 | - | - |
| `x = 10` | 20 | 10 | - |
| `y = x` | 20 | 10 | 10 |
 
### ⏰ Complexity
- Time: **O(1)**, Space: **O(1)**
### 🏋️ Practice
- Swap two variables using a third variable.
- Swap two variables without a third variable.
### ⚠️ Interview Notes
- Local variables are **not** auto-initialized. Always initialize.
- Naming rules: letters, digits, `_`; cannot start with a digit; cannot be a keyword.
- Use `const` for values that should never change.
---
 
## 2. Data Types
 
### 💡 Concept
A data type decides what kind of value a variable holds and how much memory it uses.
 
| Type | Size | Range / Use |
|------|------|-------------|
| `bool` | 1 byte | `true` / `false` |
| `char` | 1 byte | single character, -128 to 127 |
| `int` | 4 bytes | about ±2.1 × 10⁹ |
| `long long` | 8 bytes | about ±9.2 × 10¹⁸ |
| `float` | 4 bytes | ~7 decimal digits precision |
| `double` | 8 bytes | ~15 decimal digits precision |
 
### 💻 Code
```cpp
#include <iostream>
#include <climits>
using namespace std;
 
int main() {
    bool isPass = true;
    char grade = 'A';
    int count = 100;
    long long big = 10000000000LL;
    float f = 3.14f;
    double d = 3.141592653589;
 
    cout << isPass << " " << grade << " " << count << endl;
    cout << big << " " << f << " " << d << endl;
 
    cout << "int size: " << sizeof(int) << endl;
    cout << "INT_MAX: " << INT_MAX << endl;
    cout << "INT_MIN: " << INT_MIN << endl;
 
    // Overflow demo
    int m = INT_MAX;
    m = m + 1;
    cout << m << endl;          // wraps around to INT_MIN
    return 0;
}
```
 
### 🔍 Dry Run
`INT_MAX + 1` → exceeds the 4-byte range → wraps around to `-2147483648`.
 
### ⏰ Complexity
- Time: **O(1)**, Space: **O(1)**
### 🏋️ Practice
- Print the size of every data type using `sizeof`.
- Store 10¹² in a variable (which type works?).
- Print a character and its ASCII value.
### ⚠️ Interview Notes
- If a value can exceed ~2 × 10⁹, use `long long`.
- `float` literal needs an `f` suffix (`3.14f`), `long long` literal needs `LL`.
- `bool` prints as `1` or `0` unless you use `cout << boolalpha`.
- `char` is really a small integer: `'A' = 65`, `'a' = 97`, `'0' = 48`.
---
 
## 3. Type Conversion (Implicit & Explicit)
 
### 💡 Concept
Converting a value from one type to another.
 
- **Implicit conversion** (automatic): the compiler converts smaller/lower type to larger/higher type.
  Order: `bool → char → int → long long → float → double`
- **Explicit conversion** (type casting): you force the conversion yourself.
  - C-style: `(int)x`
  - C++ style: `static_cast<int>(x)` (preferred)
### 💻 Code
```cpp
#include <iostream>
using namespace std;
 
int main() {
    // ---------- IMPLICIT ----------
    int a = 5;
    double b = a;                   // int -> double (safe)
    cout << b << endl;              // 5
 
    char c = 'A';
    int asciiVal = c;               // char -> int
    cout << asciiVal << endl;       // 65
 
    int i = 7;
    double result = i + 2.5;        // i promoted to double
    cout << result << endl;         // 9.5
 
    int truncated = 9.99;           // double -> int (data loss!)
    cout << truncated << endl;      // 9 (decimal part cut, NOT rounded)
 
    // ---------- EXPLICIT ----------
    int x = 7, y = 2;
    cout << x / y << endl;                       // 3   (integer division)
    cout << (double)x / y << endl;               // 3.5 (C-style cast)
    cout << static_cast<double>(x) / y << endl;  // 3.5 (C++ cast)
 
    double pi = 3.99;
    int whole = (int)pi;                         // 3
    cout << whole << endl;
 
    char next = (char)(c + 1);                   // 'A' + 1 = 66 -> 'B'
    cout << next << endl;
 
    // Common bug: overflow happens BEFORE conversion
    int p = 100000, q = 100000;
    long long wrong = p * q;                     // int * int overflows first
    long long right = (long long)p * q;          // cast first, then multiply
    cout << wrong << " " << right << endl;
    return 0;
}
```
 
### 🔍 Dry Run
 
| Expression | Steps | Result |
|------------|-------|--------|
| `7 / 2` | int / int → integer division | `3` |
| `(double)7 / 2` | 7 → 7.0, then 7.0 / 2.0 | `3.5` |
| `int t = 9.99` | decimal part dropped | `9` |
| `'A' + 1` | 'A' → 65, 65 + 1 | `66` (as char: `'B'`) |
| `100000 * 100000` as int | exceeds INT_MAX → overflow | garbage |
| `(long long)100000 * 100000` | 64-bit multiply | `10000000000` |
 
### ⏰ Complexity
- Time: **O(1)**, Space: **O(1)**
### 🏋️ Practice
- Take two integers and print their average as a decimal.
- Convert a lowercase letter to uppercase using ASCII (`c - 32` or `c - 'a' + 'A'`).
- Convert a digit character like `'7'` to the integer `7` (`c - '0'`).
- Predict the output: `cout << 5 / 2 * 2.0;`
### ⚠️ Interview Notes
- `int / int` is always an integer division, even if stored in a `double`.
  `double d = 5 / 2;` gives `2`, not `2.5`.
- Casting must happen **before** the operation to matter: `(double)(a / b)` is wrong, `(double)a / b` is right.
- Double to int **truncates**, it does not round. Use `round()` from `<cmath>` to round.
- Mixing `int` and `unsigned int` can give surprising results: `-1 < 1u` is **false**.
- `c - '0'` is the standard trick to get the digit value of a character.
--- 
