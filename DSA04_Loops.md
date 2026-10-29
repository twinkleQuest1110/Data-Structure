# 📘C++ Basics (Logic Building)
 
> Only the core code concepts that build problem-solving logic.
1. [for Loop](#1-for-loop)
2. [while Loop](#2-while-loop)
3. [do-while Loop](#3-do-while-loop)
4. [break & continue](#4-break--continue)
4. [Nested Loops & Patterns](#5-nested-loops--patterns)
---
## 1. for Loop
 
### 💡 Concept
Use when you **know how many times** to repeat.
 
```
for (initialization; condition; update) {
    body
}
```
 
Flow: initialization (once) → check condition → run body → update → check condition again ...
 
### 💻 Code
```cpp
#include <iostream>
using namespace std;
 
int main() {
    int n = 5;
 
    // Print 1 to n
    for (int i = 1; i <= n; i++) cout << i << " ";
    cout << endl;
 
    // Sum of 1 to n
    int sum = 0;
    for (int i = 1; i <= n; i++) sum += i;
    cout << "Sum = " << sum << endl;
 
    // Factorial (use long long)
    long long fact = 1;
    for (int i = 2; i <= n; i++) fact *= i;
    cout << "Factorial = " << fact << endl;
 
    // Counting down, and step of 2
    for (int i = 10; i >= 1; i -= 2) cout << i << " ";   // 10 8 6 4 2
    cout << endl;
    return 0;
}
```
 
### 🔍 Dry Run: sum for `n = 5`
 
| i | sum before | sum after |
|---|-----------|-----------|
| 1 | 0 | 1 |
| 2 | 1 | 3 |
| 3 | 3 | 6 |
| 4 | 6 | 10 |
| 5 | 10 | 15 |
 
### ⏰ Complexity
- Time: **O(n)**, Space: **O(1)**
### 🏋️ Practice
- Print the multiplication table of n.
- Print all even numbers from 1 to 100.
- Find the sum of all odd numbers up to n.
- Calculate `a^b` using a loop.
### ⚠️ Interview Notes
- Off-by-one errors: decide carefully between `<` and `<=`.
- Factorial grows very fast: `13!` overflows `int`, `21!` overflows `long long`.
- Any of the three parts can be left empty: `for (;;)` is an infinite loop.
- A variable declared in the `for` header (`int i`) exists only inside the loop.
---
 
## 2. while Loop
 
### 💡 Concept
Use when you **don't know in advance** how many times to repeat. The condition is checked **before** each iteration, so the body may run **zero** times.
 
### 💻 Code
```cpp
#include <iostream>
using namespace std;
 
int main() {
    // Count digits
    int n = 12345, count = 0, temp = n;
    while (temp > 0) {
        count++;
        temp /= 10;
    }
    cout << "Digits = " << count << endl;       // 5
 
    // Sum of digits
    int sum = 0;
    temp = n;
    while (temp > 0) {
        sum += temp % 10;       // add last digit
        temp /= 10;             // remove last digit
    }
    cout << "Digit sum = " << sum << endl;      // 15
 
    // Reverse a number
    int rev = 0;
    temp = n;
    while (temp > 0) {
        rev = rev * 10 + temp % 10;
        temp /= 10;
    }
    cout << "Reverse = " << rev << endl;        // 54321
    return 0;
}
```
 
### 🔍 Dry Run: reverse of `123`
 
| temp | temp % 10 | rev (after) | temp (after) |
|------|-----------|-------------|--------------|
| 123 | 3 | 0×10+3 = 3 | 12 |
| 12 | 2 | 3×10+2 = 32 | 1 |
| 1 | 1 | 32×10+1 = 321 | 0 → stop |
 
### ⏰ Complexity
- Time: **O(log₁₀ n)** (one iteration per digit), Space: **O(1)**
### 🏋️ Practice
- Count the digits of a number.
- Check if a number is a palindrome.
- Find the largest digit in a number.
- Count how many times digit `d` appears in n.
### ⚠️ Interview Notes
- Always update the loop variable, or you get an **infinite loop**.
- Use a copy (`temp`) if you need the original number afterward.
- Reversing a large number can overflow `int`. Use `long long`.
- Handle `n = 0` separately in digit-count problems (the loop never runs, but `0` has 1 digit).
---
 
## 3. do-while Loop
 
### 💡 Concept
The body runs **at least once**, because the condition is checked **after** each iteration. Good for menus and input validation.
 
### 💻 Code
```cpp
#include <iostream>
using namespace std;
 
int main() {
    // Input validation: keep asking until input is valid
    int num;
    do {
        cout << "Enter a positive number: ";
        cin >> num;
    } while (num <= 0);
    cout << "You entered " << num << endl;
 
    // Simple menu
    int choice;
    do {
        cout << "\n1. Say Hi\n2. Say Bye\n0. Exit\nChoice: ";
        cin >> choice;
        if (choice == 1)      cout << "Hi!\n";
        else if (choice == 2) cout << "Bye!\n";
    } while (choice != 0);
    return 0;
}
```
 
### 🔍 Dry Run
Input sequence: `-5`, `0`, `8`
 
| Iteration | num entered | `num <= 0` | Action |
|-----------|-------------|------------|--------|
| 1 | -5 | true | repeat |
| 2 | 0 | true | repeat |
| 3 | 8 | false | exit loop |
 
### ⏰ Complexity
- Time: **O(number of iterations)**, Space: **O(1)**
### 🏋️ Practice
- Keep reading numbers until the user enters 0, then print their sum.
- Build a menu-driven calculator.
### ⚠️ Interview Notes
- Don't forget the `;` after `while (condition)` in `do-while`.
- `while` may run 0 times, `do-while` runs at least 1 time. This is a very common interview question.
---
 
## 4. break & continue
 
### 💡 Concept
- `break` exits the loop immediately.
- `continue` skips the rest of the current iteration and goes to the next.
### 💻 Code
```cpp
#include <iostream>
using namespace std;
 
int main() {
    // break: find first number divisible by 7 after 50
    for (int i = 51; i <= 100; i++) {
        if (i % 7 == 0) {
            cout << "First: " << i << endl;     // 56
            break;
        }
    }
 
    // continue: print 1 to 10 but skip multiples of 3
    for (int i = 1; i <= 10; i++) {
        if (i % 3 == 0) continue;
        cout << i << " ";                       // 1 2 4 5 7 8 10
    }
    cout << endl;
 
    // Prime check using break
    int n = 29;
    bool isPrime = (n > 1);
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            isPrime = false;
            break;
        }
    }
    cout << n << (isPrime ? " is prime" : " is not prime") << endl;
    return 0;
}
```
 
### 🔍 Dry Run: prime check for `n = 29`
 
| i | i*i | 29 % i | Action |
|---|-----|--------|--------|
| 2 | 4 | 1 | continue loop |
| 3 | 9 | 2 | continue loop |
| 4 | 16 | 1 | continue loop |
| 5 | 25 | 4 | continue loop |
| 6 | 36 | - | 36 > 29, loop ends → **prime** |
 
### ⏰ Complexity
- Prime check: Time **O(√n)**, Space **O(1)**
### 🏋️ Practice
- Print all prime numbers up to n.
- Find the first number divisible by both 3 and 5 after a given number.
### ⚠️ Interview Notes
- `break` only exits the **innermost** loop.
- In a `while` loop, put the update **before** `continue`, or you create an infinite loop.
- Looping only up to `√n` is the standard optimization for prime checking.
- Handle `n <= 1` separately: they are not prime.
---
 
## 5. Nested Loops & Patterns
 
### 💡 Concept
A loop inside a loop. The **outer loop controls rows**, the **inner loop controls columns**. For every row `i`, ask: *how many spaces? how many stars/numbers?*
 
### 💻 Code
```cpp
#include <iostream>
using namespace std;
 
int main() {
    int n = 4;
 
    // 1) Right triangle
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) cout << "* ";
        cout << "\n";
    }
    cout << endl;
 
    // 2) Number triangle
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) cout << j << " ";
        cout << "\n";
    }
    cout << endl;
 
    // 3) Pyramid
    for (int i = 1; i <= n; i++) {
        for (int s = 1; s <= n - i; s++) cout << " ";       // spaces
        for (int j = 1; j <= 2 * i - 1; j++) cout << "*";   // stars
        cout << "\n";
    }
    cout << endl;
 
    // 4) Inverted triangle
    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= i; j++) cout << "* ";
        cout << "\n";
    }
    return 0;
}
```
 
### 🔍 Dry Run: Pyramid, `n = 4`
 
| Row i | Spaces (n - i) | Stars (2i - 1) | Output |
|-------|----------------|----------------|--------|
| 1 | 3 | 1 | `   *` |
| 2 | 2 | 3 | `  ***` |
| 3 | 1 | 5 | ` *****` |
| 4 | 0 | 7 | `*******` |
 
### ⏰ Complexity
- Time: **O(n²)**, Space: **O(1)**
### 🏋️ Practice
- Hollow square
- Floyd's triangle (1, 2 3, 4 5 6, ...)
- Diamond pattern
- Butterfly pattern
- Pascal's triangle
### ⚠️ Interview Notes
- Method: write the row number, spaces count, and stars count in a table, then find the formula in terms of `i` and `n`.
- Print `"\n"` once per row (after the inner loop), not inside it.
- Total iterations of a nested loop = outer × inner (this is where O(n²) comes from).
---
 
