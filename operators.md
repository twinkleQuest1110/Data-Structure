# 📘 C++ Basics (Logic Building)
 
> Only the core code concepts that build problem-solving logic.
 
## 📑 OPERATORS

### 💡 Concept
 
| Category | Operators |
|----------|-----------|
| Arithmetic | `+  -  *  /  %` |
| Relational | `==  !=  <  >  <=  >=` |
| Logical | `&&  \|\|  !` |
| Assignment | `=  +=  -=  *=  /=  %=` |
| Increment / Decrement | `++  --` (pre and post) |
 
### 💻 Code
```cpp
#include <iostream>
using namespace std;
 
int main() {
    int a = 17, b = 5;
    cout << a + b << " " << a - b << " " << a * b << endl;   // 22 12 85
    cout << a / b << " " << a % b << endl;                   // 3 2
 
    cout << (a > b) << endl;                    // 1 (true)
    cout << (a > 10 && b < 3) << endl;          // 0 (false)
    cout << (a > 10 || b < 3) << endl;          // 1 (true)
    cout << !(a == b) << endl;                  // 1 (true)
 
    int x = 5;
    cout << x++ << endl;        // prints 5, then x = 6   (post)
    cout << ++x << endl;        // x = 7, then prints 7   (pre)
 
    x += 3;                     // x = x + 3 -> 10
    x *= 2;                     // x = x * 2 -> 20
    cout << x << endl;
    return 0;
}
```
 
### 🔍 Dry Run
 
| Statement | x after | Printed |
|-----------|---------|---------|
| `int x = 5` | 5 | - |
| `x++` | 6 | 5 |
| `++x` | 7 | 7 |
| `x += 3` | 10 | - |
| `x *= 2` | 20 | - |
 
### ⏰ Complexity
- Time: **O(1)**, Space: **O(1)**
### 🏋️ Practice
- Check even/odd using `%`.
- Get the last digit of a number (`n % 10`) and remove it (`n / 10`).
- Check if a number is divisible by both 3 and 5.
### ⚠️ Interview Notes
- `=` assigns, `==` compares. `if (x = 5)` is a classic bug.
- `%` with negative numbers: `-7 % 3 = -1` in C++.
- `&&` and `||` **short-circuit**: in `a && b`, if `a` is false, `b` is never evaluated.
- `n % 10` gives the last digit, `n / 10` removes it. This pair is used in many digit problems.
---
 
