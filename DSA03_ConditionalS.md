# 📘 C++ Basics (Logic Building)
 
> Only the core code concepts that build problem-solving logic.
1. [if / else if / else](#5-if--else-if--else)
2. [switch & Ternary](#6-switch--ternary)

## if / else if / else
 
### 💡 Concept
Run different code depending on a condition. Conditions are checked top to bottom, and **only the first true branch runs**.
 
### 💻 Code
```cpp
#include <iostream>
using namespace std;
 
int main() {
    int marks;
    cin >> marks;
 
    if (marks < 0 || marks > 100) {
        cout << "Invalid\n";
    } else if (marks >= 90) {
        cout << "Grade A\n";
    } else if (marks >= 75) {
        cout << "Grade B\n";
    } else if (marks >= 50) {
        cout << "Grade C\n";
    } else {
        cout << "Fail\n";
    }
 
    // Nested if: largest of three numbers
    int a = 12, b = 30, c = 21;
    if (a >= b) {
        if (a >= c) cout << a << " is largest\n";
        else        cout << c << " is largest\n";
    } else {
        if (b >= c) cout << b << " is largest\n";
        else        cout << c << " is largest\n";
    }
    return 0;
}
```
 
### 🔍 Dry Run
Input `marks = 80`
 
| Check | Result |
|-------|--------|
| `80 < 0 \|\| 80 > 100` | false |
| `80 >= 90` | false |
| `80 >= 75` | **true** → prints `Grade B` |
| remaining branches | skipped |
 
Largest of (12, 30, 21): `12 >= 30` false → else → `30 >= 21` true → prints `30`.
 
### ⏰ Complexity
- Time: **O(1)**, Space: **O(1)**
### 🏋️ Practice
- Check positive, negative, or zero.
- Check if a year is a leap year.
- Check whether a character is a vowel, consonant, digit, or special character.
- Check whether three sides form a valid triangle.
### ⚠️ Interview Notes
- Always handle **invalid input** and **edge cases** first.
- Leap year: `(y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)`.
- Put the most restrictive condition first (`>= 90` before `>= 75`).
- Always use `{ }` even for a single statement; it avoids bugs later.
---
 
## switch & Ternary
 
### 💡 Concept
- `switch` picks one branch based on the exact value of an int/char.
- Ternary `cond ? a : b` is a one-line if-else that gives a value.
### 💻 Code
```cpp
#include <iostream>
using namespace std;
 
int main() {
    // Simple calculator with switch
    double a = 20, b = 4;
    char op = '/';
 
    switch (op) {
        case '+': cout << a + b << endl; break;
        case '-': cout << a - b << endl; break;
        case '*': cout << a * b << endl; break;
        case '/':
            if (b != 0) cout << a / b << endl;
            else        cout << "Division by zero\n";
            break;
        default:  cout << "Invalid operator\n";
    }
 
    // Ternary
    int n = 7;
    cout << (n % 2 == 0 ? "Even" : "Odd") << endl;
    return 0;
}
```
 
### 🔍 Dry Run
`op = '/'` → jumps to `case '/'` → `b != 0` true → prints `5` → `break` exits the switch.
 
### ⏰ Complexity
- Time: **O(1)**, Space: **O(1)**
### 🏋️ Practice
- Print the day name from a number 1-7.
- Check vowel or consonant using `switch`.
### ⚠️ Interview Notes
- Forgetting `break` causes **fall-through** into the next case.
- `switch` works on `int` and `char`, not on `string` or `double`.
- Keep ternaries simple; deeply nested ternaries are unreadable.
---
 
