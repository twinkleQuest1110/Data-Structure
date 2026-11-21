# 📗 12- Recursion in C++

> Recursion is when a function **calls itself** to solve a smaller version of the same problem.

## 📑 Contents
1. [Concept & Call Stack](#1-concept--call-stack)
2. [How to Think Recursively](#2-how-to-think-recursively)
3. [Basic Programs](#3-basic-programs)
4. [Fibonacci & Tree Recursion](#4-fibonacci--tree-recursion)
5. [Recursion on Arrays & Strings](#5-recursion-on-arrays--strings)
6. [GCD & Fast Power](#6-gcd--fast-power)
7. [Binary Search (Recursive)](#7-binary-search-recursive)
8. [Tower of Hanoi](#8-tower-of-hanoi)
9. [Subsets (Intro to Backtracking)](#9-subsets-intro-to-backtracking)
10. [Head vs Tail Recursion](#10-head-vs-tail-recursion)
11. [Mistakes, Practice & Checklist](#11-mistakes-practice--checklist)

---

## 1. Concept & Call Stack

### 💡 Concept
Every recursive function needs:
1. **Base case**: the simplest input, answered directly (this stops the recursion)
2. **Recursive case**: reduce the problem and call itself

Each call gets its own **stack frame** (its own copy of the parameters and local variables). Calls pile up going down, then return values flow back up.

```
factorial(4)
 └─ 4 * factorial(3)
          └─ 3 * factorial(2)
                   └─ 2 * factorial(1)
                            └─ returns 1      <- base case
                   └─ 2 * 1 = 2
          └─ 3 * 2 = 6
 └─ 4 * 6 = 24
```

### 💻 Code
```cpp
#include <iostream>
using namespace std;

long long factorial(int n) {
    if (n <= 1) return 1;                // base case
    return n * factorial(n - 1);         // recursive case
}

int main() {
    cout << factorial(5) << endl;        // 120
    return 0;
}
```

### 🔍 Dry Run: `factorial(4)`

| Call stack (top = latest) | Action |
|---------------------------|--------|
| f(4) | needs f(3) |
| f(4), f(3) | needs f(2) |
| f(4), f(3), f(2) | needs f(1) |
| f(4), f(3), f(2), f(1) | base case, returns **1** |
| f(4), f(3), f(2) | returns 2 × 1 = **2** |
| f(4), f(3) | returns 3 × 2 = **6** |
| f(4) | returns 4 × 6 = **24** |

### ⏰ Complexity
- Time: **O(n)**, Space: **O(n)** (call stack depth)

### ⚠️ Interview Notes
- Missing or unreachable base case → infinite recursion → **stack overflow**.
- Recursion always uses stack space equal to the **maximum depth**. Mention it in complexity analysis.

---

## 2. How to Think Recursively

1. **Define what the function does** (e.g. "returns the sum of 1 to n").
2. **Write the base case** (smallest input, e.g. `n == 0`).
3. **Trust the function** for the smaller input (`sum(n-1)` is correct) and **combine** it with the current step: `n + sum(n-1)`.

```
sum(n) = n + sum(n - 1)        sum(0) = 0
```

> Don't trace every call in your head. Check the base case and that each call moves **closer** to it.

---

## 3. Basic Programs

### 💻 Code
```cpp
// Print 1 to n  (recurse first, print on the way back)
void print1ToN(int n) {
    if (n == 0) return;
    print1ToN(n - 1);
    cout << n << " ";
}

// Print n to 1  (print first, then recurse)
void printNTo1(int n) {
    if (n == 0) return;
    cout << n << " ";
    printNTo1(n - 1);
}

// Sum of 1 to n
int sumN(int n) {
    if (n == 0) return 0;
    return n + sumN(n - 1);
}

// Power: a^b
long long power(int a, int b) {
    if (b == 0) return 1;
    return a * power(a, b - 1);
}

// Sum of digits
int digitSum(int n) {
    if (n == 0) return 0;
    return n % 10 + digitSum(n / 10);
}

// Count digits
int countDigits(int n) {
    if (n < 10) return 1;
    return 1 + countDigits(n / 10);
}
```

### 🔍 Dry Run

**`print1ToN(3)`**: calls go 3 → 2 → 1 → 0 (base). Printing happens **while returning**: `1 2 3`.
**`printNTo1(3)`**: prints **before** each call: `3 2 1`.

**`digitSum(123)`**

| Call | Returns |
|------|---------|
| digitSum(123) | 3 + digitSum(12) |
| digitSum(12) | 2 + digitSum(1) |
| digitSum(1) | 1 + digitSum(0) |
| digitSum(0) | **0** (base) |

Unwinding: 1 + 0 = 1 → 2 + 1 = 3 → 3 + 3 = **6**.

### ⏰ Complexity

| Function | Time | Space |
|----------|------|-------|
| print, sum, factorial, power | O(n) / O(b) | O(n) / O(b) |
| digitSum, countDigits | O(log₁₀ n) | O(log₁₀ n) |

### ⚠️ Interview Notes
- **Order matters**: code before the recursive call runs on the way **down**; code after it runs on the way **up**.
- `countDigits` base case is `n < 10` (so `0` returns 1).

---

## 4. Fibonacci & Tree Recursion

### 💡 Concept
When a function calls itself **more than once**, calls form a tree. Naive Fibonacci recomputes the same values many times.

```
                 fib(4)
               /        \
          fib(3)        fib(2)
          /    \        /    \
     fib(2)  fib(1)  fib(1) fib(0)
     /    \
 fib(1) fib(0)

fib(2) is computed twice, fib(1) three times ...
```

**Memoization** stores results so each value is computed **once**.

### 💻 Code
```cpp
// Naive: O(2^n)
int fib(int n) {
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
}

// Memoized: O(n)
long long fibMemo(int n, long long memo[]) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];                       // already computed
    return memo[n] = fibMemo(n - 1, memo) + fibMemo(n - 2, memo);
}

int main() {
    long long memo[51];
    fill(memo, memo + 51, -1);
    cout << fib(6) << endl;              // 8
    cout << fibMemo(50, memo) << endl;   // 12586269025
    return 0;
}
```

### 🔍 Dry Run: `fib(4)`
`fib(4) = fib(3) + fib(2) = (fib(2) + fib(1)) + (fib(1) + fib(0)) = ((1 + 0) + 1) + (1 + 0) = 3`

### ⏰ Complexity

| Version | Time | Space |
|---------|------|-------|
| Naive | **O(2ⁿ)** | O(n) |
| Memoized | **O(n)** | O(n) |

### ⚠️ Interview Notes
- Naive `fib(50)` takes billions of calls; memoized needs about 100.
- Memoization is the first step to **Dynamic Programming**.
- Use `long long`: `int` overflows after `fib(46)`.

---

## 5. Recursion on Arrays & Strings

### 💡 Concept
Shrink the problem by **one element** each call: either reduce `n`, or move an index / two pointers inward.

### 💻 Code
```cpp
// Sum of array
int sumArr(const int a[], int n) {
    if (n == 0) return 0;
    return a[n - 1] + sumArr(a, n - 1);
}

// Maximum of array
int maxArr(const int a[], int n) {
    if (n == 1) return a[0];
    return max(a[n - 1], maxArr(a, n - 1));
}

// Is array sorted (ascending)?
bool isSorted(const int a[], int n) {
    if (n <= 1) return true;
    return a[n - 2] <= a[n - 1] && isSorted(a, n - 1);
}

// Reverse array (two pointers)
void reverseArr(int a[], int l, int r) {
    if (l >= r) return;
    swap(a[l], a[r]);
    reverseArr(a, l + 1, r - 1);
}

// Palindrome string
bool isPalindrome(const string &s, int l, int r) {
    if (l >= r) return true;
    if (s[l] != s[r]) return false;
    return isPalindrome(s, l + 1, r - 1);
}
```

### 🔍 Dry Run: `maxArr({4, 9, 2}, 3)`

| Call | Returns |
|------|---------|
| maxArr(a, 3) | max(a[2] = 2, maxArr(a, 2)) |
| maxArr(a, 2) | max(a[1] = 9, maxArr(a, 1)) |
| maxArr(a, 1) | **4** (base) |

Unwinding: max(9, 4) = 9 → max(2, 9) = **9**.

### ⏰ Complexity
All: **O(n)** time, **O(n)** stack space (the iterative versions use O(1) space)

### ⚠️ Interview Notes
- Pass **indexes** (`l`, `r`), not sub-arrays, so you don't copy data.
- Pass strings by `const &` to avoid copying on every call.

---

## 6. GCD & Fast Power

### 💻 Code
```cpp
// Euclid's algorithm
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Fast power: O(log b) instead of O(b)
long long fastPower(long long a, int b) {
    if (b == 0) return 1;
    long long half = fastPower(a, b / 2);
    if (b % 2 == 0) return half * half;
    return half * half * a;
}
```

### 🔍 Dry Run

**`gcd(48, 18)`**: gcd(48, 18) → gcd(18, 12) → gcd(12, 6) → gcd(6, 0) → **6**

**`fastPower(2, 10)`**

| Call | Result |
|------|--------|
| fastPower(2, 10) | half = fastPower(2, 5) → 32, even → 32 × 32 = **1024** |
| fastPower(2, 5) | half = fastPower(2, 2) → 4, odd → 4 × 4 × 2 = 32 |
| fastPower(2, 2) | half = fastPower(2, 1) → 2, even → 2 × 2 = 4 |
| fastPower(2, 1) | half = fastPower(2, 0) → 1, odd → 1 × 1 × 2 = 2 |

### ⏰ Complexity
- `gcd`: **O(log(min(a, b)))**
- `fastPower`: **O(log b)** time, O(log b) space

### ⚠️ Interview Notes
- Compute `fastPower(a, b / 2)` **once** and store it. Calling it twice would make it O(b) again.
- Add `% MOD` for large powers in competitive problems.

---

## 7. Binary Search (Recursive)

### 💻 Code
```cpp
int binarySearch(const int a[], int low, int high, int key) {
    if (low > high) return -1;                       // base case: not found
    int mid = low + (high - low) / 2;
    if (a[mid] == key) return mid;
    if (a[mid] < key)  return binarySearch(a, mid + 1, high, key);
    return binarySearch(a, low, mid - 1, key);
}
// Call: binarySearch(arr, 0, n - 1, key)
```

### 🔍 Dry Run: key = 23 in `{2, 5, 8, 12, 16, 23, 38}`

| low | high | mid | a[mid] | Action |
|-----|------|-----|--------|--------|
| 0 | 6 | 3 | 12 | search right half |
| 4 | 6 | 5 | 23 | found, return 5 |

### ⏰ Complexity
**O(log n)** time, **O(log n)** stack space (iterative version: O(1) space)

---

## 8. Tower of Hanoi

### 💡 Concept
Move `n` disks from peg A to peg C using peg B, never placing a larger disk on a smaller one.

To move `n` disks:
1. Move the top `n − 1` disks from **A → B**
2. Move the biggest disk from **A → C**
3. Move the `n − 1` disks from **B → C**

### 💻 Code
```cpp
void hanoi(int n, char from, char to, char aux) {
    if (n == 0) return;
    hanoi(n - 1, from, aux, to);
    cout << "Move disk " << n << " from " << from << " to " << to << "\n";
    hanoi(n - 1, aux, to, from);
}
// hanoi(2, 'A', 'C', 'B');
```

### 🔍 Dry Run: `hanoi(2, 'A', 'C', 'B')`

```
Move disk 1 from A to B
Move disk 2 from A to C
Move disk 1 from B to C
```

### ⏰ Complexity
- Moves = **2ⁿ − 1**, so Time: **O(2ⁿ)**, Space: O(n)

---

## 9. Subsets (Intro to Backtracking)

### 💡 Concept
For each element make a choice: **exclude** it or **include** it. After exploring, **undo** the choice (backtrack).

```
              []
         /          \
   exclude 1      include 1
    /     \         /     \
  []     [2]      [1]    [1,2]
```

### 💻 Code
```cpp
#include <vector>

void subsets(const int a[], int n, int i, vector<int> &cur) {
    if (i == n) {                                  // decided about every element
        cout << "{ ";
        for (int x : cur) cout << x << " ";
        cout << "}\n";
        return;
    }
    subsets(a, n, i + 1, cur);                     // exclude a[i]
    cur.push_back(a[i]);                           // include a[i]
    subsets(a, n, i + 1, cur);
    cur.pop_back();                                // undo (backtrack)
}

int main() {
    int a[] = {1, 2};
    vector<int> cur;
    subsets(a, 2, 0, cur);                         // { }, { 2 }, { 1 }, { 1 2 }
    return 0;
}
```

### ⏰ Complexity
- Time: **O(2ⁿ × n)** (2ⁿ subsets, each printed in O(n)), Space: O(n)

### ⚠️ Interview Notes
- `pop_back()` is the **backtracking step**. Without it, `cur` keeps stale elements.
- The same include / exclude pattern solves permutations, N-Queens and sudoku.

---

## 10. Head vs Tail Recursion

| Type | Meaning | Example |
|------|---------|---------|
| **Head** | recursive call comes **first**, work after | `print1ToN` (prints on return) |
| **Tail** | recursive call is the **last** thing done | `factorialTail` below |

```cpp
long long factorialTail(int n, long long acc = 1) {
    if (n <= 1) return acc;
    return factorialTail(n - 1, acc * n);     // nothing left to do after the call
}
```

- Tail recursion can be turned into a **loop** by the compiler (no extra stack), but C++ does **not guarantee** this.
- **Recursion vs iteration:** recursion is clearer for trees, divide and conquer and backtracking; loops are faster and use O(1) stack for simple counting.

---

## 11. Mistakes, Practice & Checklist

### ⚠️ Common Mistakes

| Mistake | Fix |
|---------|-----|
| No base case | Always write it first |
| Call doesn't move toward the base case (`f(n)` calls `f(n)`) | Reduce `n`, shrink the range |
| Stack overflow (depth ≈ 10⁴ to 10⁵ and beyond) | Use a loop or memoized iterative DP |
| Naive tree recursion (`fib`) | Add memoization |
| Forgetting to return the recursive result | `return f(n - 1)` |
| Calling `fastPower` twice in one expression | Store the result in a variable |
| Forgetting to undo choices in backtracking | `pop_back()` after the call |

### 🏋️ Practice
- 🟢 Print 1 to n and n to 1; sum of n; factorial; count digits; sum of array; check if a string is a palindrome.
- 🟡 Reverse a string; nth Fibonacci with memoization; `a^b` in O(log b); count occurrences of a digit; first and last index of an element; convert decimal to binary recursively.
- 🟠 Tower of Hanoi (count the moves); all permutations of a string; generate all balanced parentheses; subset sum equal to k; N-Queens.

### ✅ Checklist
- [ ] I can state the base case and the recursive case of any problem
- [ ] I can draw the call stack for a small input
- [ ] I know what runs on the way down and what runs on the way up
- [ ] I can explain why naive Fibonacci is O(2ⁿ) and fix it with memoization
- [ ] I can write recursion on arrays and strings using an index
- [ ] I know recursion uses O(depth) stack space and can cause stack overflow
- [ ] I can write include / exclude and undo for subsets
- [ ] I know when to prefer a loop over recursion
