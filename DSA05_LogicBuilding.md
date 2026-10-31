# 🧩 Logic Building Programs (C++ Basics)

> Classic programs that combine variables, type conversion, if-else and loops.
> Solve each one yourself first, then compare with the code.

## 🧠 How to Think About Any Problem

1. **Understand**: what is the input and what is the expected output?
2. **Try small examples by hand**: write 2 or 3 sample inputs and their outputs.
3. **Find the pattern**: what repeats? That is your loop.
4. **Write the steps in plain English** before writing code.
5. **Check edge cases**: `0`, `1`, negative numbers, very large numbers.
6. **Dry run** your code on a small input.

## 📑 Index

| Level | Programs |
|-------|----------|
| 🟢 Level 1: Number Basics | [Even/Odd](#1-evenodd) · [Sum of n](#2-sum-of-first-n-natural-numbers) · [Factorial](#3-factorial) · [Power](#4-power-ab) · [Table](#5-multiplication-table) · [Largest of 3](#6-largest-of-three-numbers) · [Leap Year](#7-leap-year) · [Swap](#8-swap-two-numbers) · [Read until 0](#9-sum-and-average-until-0-is-entered) |
| 🟡 Level 2: Digit Problems | [Count Digits](#10-count-digits) · [Sum of Digits](#11-sum-of-digits) · [Reverse](#12-reverse-a-number) · [Palindrome](#13-palindrome-number) · [Armstrong](#14-armstrong-number) · [Largest Digit](#15-largest-and-smallest-digit) · [Digit Frequency](#16-count-occurrences-of-a-digit) |
| 🟠 Level 3: Number Theory | [Prime](#17-prime-check) · [Primes in Range](#18-primes-in-a-range) · [GCD & LCM](#19-gcd-and-lcm) · [Factors](#20-factors-of-a-number) · [Perfect](#21-perfect-number) · [Prime Factors](#22-prime-factorization) · [Binary Conversion](#23-decimal--binary-conversion) |
| 🔵 Level 4: Series | [Fibonacci](#24-fibonacci-series) · [Harmonic Series](#25-sum-of-series-1--12--13--) |
| 🟣 Level 5: Characters | [Character Type](#26-character-classification) · [Case Conversion](#27-case-conversion-using-ascii) |

> 📌 Every snippet below is a function. To run one, put it above `main()` and call it from `main()`, with `#include <iostream>` and `using namespace std;` at the top.

---

# 🟢 Level 1: Number Basics

## 1. Even/Odd

**Logic:** a number is even if dividing by 2 leaves remainder 0.

```cpp
bool isEven(int n) {
    return n % 2 == 0;
}
// isEven(10) -> true, isEven(7) -> false, isEven(-3) -> false
```

**Dry run:** `7 % 2 = 1` → not 0 → odd.
**Complexity:** O(1) time, O(1) space.
**Note:** Check `n % 2 == 0`, not `n % 2 == 1`, because `-3 % 2` is `-1` in C++.

---

## 2. Sum of First n Natural Numbers

**Logic:** add 1 + 2 + ... + n. There is also a direct formula: `n(n+1)/2`.

```cpp
long long sumLoop(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) sum += i;
    return sum;
}

long long sumFormula(int n) {
    return (long long)n * (n + 1) / 2;     // cast first to avoid int overflow
}
// n = 5 -> 15
```

**Dry run (n = 5):** sum goes 0 → 1 → 3 → 6 → 10 → 15.
**Complexity:** loop O(n), formula **O(1)**.
**Note:** The formula is faster. Always ask: "Is there a formula?"

---

## 3. Factorial

**Logic:** `n! = 1 × 2 × 3 × ... × n`, and `0! = 1`.

```cpp
long long factorial(int n) {
    long long fact = 1;
    for (int i = 2; i <= n; i++) fact *= i;
    return fact;
}
// factorial(5) -> 120, factorial(0) -> 1
```

**Dry run (n = 4):** fact = 1 → ×2 = 2 → ×3 = 6 → ×4 = 24.
**Complexity:** O(n) time, O(1) space.
**Note:** `21!` overflows even `long long`. Factorial is not defined for negative numbers.

---

## 4. Power (a^b)

**Logic:** multiply `a` by itself `b` times.

```cpp
long long power(int a, int b) {
    long long result = 1;
    for (int i = 0; i < b; i++) result *= a;
    return result;
}
// power(2, 10) -> 1024, power(5, 0) -> 1
```

**Dry run (2^3):** result = 1 → 2 → 4 → 8.
**Complexity:** O(b) time, O(1) space.
**Note:** Prefer this over `pow()` for integers, because `pow()` returns a `double` and can be slightly off.

---

## 5. Multiplication Table

**Logic:** print `n × i` for i from 1 to 10.

```cpp
void table(int n) {
    for (int i = 1; i <= 10; i++) {
        cout << n << " x " << i << " = " << n * i << "\n";
    }
}
// table(7) -> 7 x 1 = 7 ... 7 x 10 = 70
```

**Complexity:** O(1) for fixed 10 rows (O(k) for k rows).

---

## 6. Largest of Three Numbers

**Logic:** assume the first is the largest, then compare with the others.

```cpp
int largest(int a, int b, int c) {
    int mx = a;
    if (b > mx) mx = b;
    if (c > mx) mx = c;
    return mx;
}
// largest(12, 30, 21) -> 30
```

**Dry run:** mx = 12 → `30 > 12` so mx = 30 → `21 > 30` false → answer 30.
**Complexity:** O(1).
**Note:** This "assume first, then update" idea is the base of finding max in an array.

---

## 7. Leap Year

**Logic:** divisible by 4 **and** not by 100, **or** divisible by 400.

```cpp
bool isLeap(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
// 2024 -> true, 1900 -> false, 2000 -> true
```

**Dry run (1900):** `1900 % 4 == 0` true, but `1900 % 100 != 0` false → first part false; `1900 % 400 != 0` → false → not leap.
**Complexity:** O(1).

---

## 8. Swap Two Numbers

**Logic:** three ways, and each one teaches something.

```cpp
void swapTemp(int &a, int &b) {          // 1) temporary variable (clearest)
    int temp = a;
    a = b;
    b = temp;
}

void swapArithmetic(int &a, int &b) {    // 2) without a third variable
    a = a + b;
    b = a - b;
    a = a - b;
}

void swapBuiltIn(int &a, int &b) {       // 3) built-in
    swap(a, b);
}
```

**Dry run (a = 5, b = 8) for method 2:**

| Step | a | b |
|------|---|---|
| start | 5 | 8 |
| `a = a + b` | 13 | 8 |
| `b = a - b` | 13 | 5 |
| `a = a - b` | 8 | 5 |

**Complexity:** O(1).
**Note:** Method 2 can overflow for large values. In practice use method 1 or `swap()`.

---

## 9. Sum and Average Until 0 is Entered

**Logic:** keep reading numbers. Stop when the user enters 0. Use a loop whose count is unknown.

```cpp
void sumUntilZero() {
    int x, count = 0;
    long long sum = 0;

    cin >> x;
    while (x != 0) {
        sum += x;
        count++;
        cin >> x;                // read the next value at the end of the loop
    }

    if (count > 0)
        cout << "Sum = " << sum << ", Average = " << (double)sum / count << endl;
    else
        cout << "No numbers entered\n";
}
// Input: 4 6 8 0  -> Sum = 18, Average = 6
```

**Dry run (input 4 6 8 0):**

| x | sum | count |
|---|-----|-------|
| 4 | 4 | 1 |
| 6 | 10 | 2 |
| 8 | 18 | 3 |
| 0 | loop ends | |

**Complexity:** O(n) for n inputs.
**Note:** `(double)sum / count` uses explicit type conversion to get a decimal average. Check `count > 0` to avoid division by zero.

---

# 🟡 Level 2: Digit Problems

> Core trick: `n % 10` gives the **last digit**, `n / 10` **removes** the last digit.

## 10. Count Digits

```cpp
int countDigits(int n) {
    if (n == 0) return 1;
    if (n < 0) n = -n;
    int count = 0;
    while (n > 0) {
        count++;
        n /= 10;
    }
    return count;
}
// 12345 -> 5, 0 -> 1
```

**Dry run (12345):** n goes 12345 → 1234 → 123 → 12 → 1 → 0, count = 5.
**Complexity:** O(log₁₀ n) time, O(1) space.
**Note:** Handle `0` separately, since the loop would not run for it.

---

## 11. Sum of Digits

```cpp
int sumOfDigits(int n) {
    if (n < 0) n = -n;
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}
// 1234 -> 10
```

**Dry run (1234):**

| n | n % 10 | sum |
|---|--------|-----|
| 1234 | 4 | 4 |
| 123 | 3 | 7 |
| 12 | 2 | 9 |
| 1 | 1 | 10 |

**Complexity:** O(log₁₀ n).

---

## 12. Reverse a Number

```cpp
long long reverseNumber(int n) {
    bool negative = n < 0;
    if (negative) n = -n;

    long long rev = 0;
    while (n > 0) {
        rev = rev * 10 + n % 10;     // push last digit to the back of rev
        n /= 10;
    }
    return negative ? -rev : rev;
}
// 1200 -> 21, 123 -> 321
```

**Dry run (123):** rev = 0 → 3 → 32 → 321.
**Complexity:** O(log₁₀ n).
**Note:** Trailing zeros disappear (`1200 → 21`). Use `long long` to avoid overflow.

---

## 13. Palindrome Number

**Logic:** a number is a palindrome if it equals its reverse.

```cpp
bool isPalindrome(int n) {
    if (n < 0) return false;
    long long rev = 0;
    int temp = n;
    while (temp > 0) {
        rev = rev * 10 + temp % 10;
        temp /= 10;
    }
    return rev == n;
}
// 12321 -> true, 123 -> false
```

**Dry run (121):** reverse = 121 → equals original → true.
**Complexity:** O(log₁₀ n).
**Note:** Keep a copy of the original (`temp`), because the loop destroys the number.

---

## 14. Armstrong Number

**Logic:** the sum of each digit raised to the power of the digit count equals the number. Example: `153 = 1³ + 5³ + 3³`.

```cpp
// Uses countDigits() and power() from the programs above
bool isArmstrong(int n) {
    int digits = countDigits(n);
    long long sum = 0;
    int temp = n;
    while (temp > 0) {
        int d = temp % 10;
        sum += power(d, digits);
        temp /= 10;
    }
    return sum == n;
}
// 153 -> true, 9474 -> true, 123 -> false
```

**Dry run (153):** digits = 3 → `1 + 125 + 27 = 153` → true.
**Complexity:** O(log n × log n) in the worst case.

---

## 15. Largest and Smallest Digit

```cpp
void largestSmallestDigit(int n) {
    if (n < 0) n = -n;
    int mx = 0, mn = 9;
    if (n == 0) { mx = mn = 0; }
    while (n > 0) {
        int d = n % 10;
        if (d > mx) mx = d;
        if (d < mn) mn = d;
        n /= 10;
    }
    cout << "Largest = " << mx << ", Smallest = " << mn << endl;
}
// 48215 -> Largest = 8, Smallest = 1
```

**Dry run (48215):** digits seen 5, 1, 2, 8, 4 → mx updates 5 → 8, mn updates 5 → 1.
**Complexity:** O(log₁₀ n).
**Note:** Start `mx` at the lowest possible digit (0) and `mn` at the highest (9).

---

## 16. Count Occurrences of a Digit

```cpp
int countDigit(int n, int target) {
    if (n < 0) n = -n;
    if (n == 0) return target == 0 ? 1 : 0;
    int count = 0;
    while (n > 0) {
        if (n % 10 == target) count++;
        n /= 10;
    }
    return count;
}
// countDigit(727377, 7) -> 4
```

**Dry run (727377, target 7):** digits from the end: 7, 7, 3, 7, 2, 7 → four 7s.
**Complexity:** O(log₁₀ n).

---

# 🟠 Level 3: Number Theory

## 17. Prime Check

**Logic:** a prime has exactly two divisors: 1 and itself. If a number has a divisor, it has one at most `√n`, so we only check up to `√n`.

```cpp
bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; (long long)i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}
// 29 -> true, 1 -> false, 2 -> true, 100 -> false
```

**Dry run (n = 29):** i = 2, 3, 4, 5 checked (since 6 × 6 = 36 > 29), none divides 29 → prime.
**Complexity:** O(√n) time, O(1) space.
**Note:** `1` is not prime, `2` is the only even prime. Writing `i * i <= n` avoids calling `sqrt()`.

---

## 18. Primes in a Range

```cpp
// Uses isPrime() from above
void primesInRange(int low, int high) {
    for (int num = low; num <= high; num++) {
        if (isPrime(num)) cout << num << " ";
    }
    cout << endl;
}
// primesInRange(10, 30) -> 11 13 17 19 23 29
```

**Complexity:** O((high − low) × √high).
**Note:** For large ranges, use the Sieve of Eratosthenes (covered later).

---

## 19. GCD and LCM

**Logic (Euclid):** `gcd(a, b) = gcd(b, a % b)`, and stop when `b` becomes 0. Then `lcm = a × b / gcd`.

```cpp
int gcd(int a, int b) {
    while (b != 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

long long lcm(int a, int b) {
    return (long long)a / gcd(a, b) * b;    // divide first to avoid overflow
}
// gcd(48, 18) -> 6, lcm(4, 6) -> 12
```

**Dry run gcd(48, 18):**

| a | b | r = a % b |
|---|---|-----------|
| 48 | 18 | 12 |
| 18 | 12 | 6 |
| 12 | 6 | 0 |
| 6 | 0 | answer 6 |

**Complexity:** O(log(min(a, b))).

---

## 20. Factors of a Number

```cpp
void printFactors(int n) {
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) cout << i << " ";
    }
    cout << endl;
}
// printFactors(12) -> 1 2 3 4 6 12
```

**Complexity:** O(n).
**Optimization:** divisors come in pairs `(i, n/i)`, so looping to `√n` is enough (O(√n)).

---

## 21. Perfect Number

**Logic:** a number equals the sum of its proper divisors (all divisors except itself). Example: `6 = 1 + 2 + 3`.

```cpp
bool isPerfect(int n) {
    if (n < 2) return false;
    int sum = 0;
    for (int i = 1; i <= n / 2; i++) {
        if (n % i == 0) sum += i;
    }
    return sum == n;
}
// 6 -> true, 28 -> true, 12 -> false
```

**Dry run (28):** divisors 1, 2, 4, 7, 14 → sum = 28 → true.
**Complexity:** O(n).
**Note:** No proper divisor of `n` is bigger than `n / 2`.

---

## 22. Prime Factorization

**Logic:** keep dividing by the smallest factor while it divides, then move to the next.

```cpp
void primeFactors(int n) {
    for (int i = 2; (long long)i * i <= n; i++) {
        while (n % i == 0) {
            cout << i << " ";
            n /= i;
        }
    }
    if (n > 1) cout << n;       // leftover is a prime > sqrt(original n)
    cout << endl;
}
// primeFactors(60) -> 2 2 3 5
```

**Dry run (n = 60):**

| i | action | n after |
|---|--------|---------|
| 2 | divides, print 2 | 30 |
| 2 | divides, print 2 | 15 |
| 3 | divides, print 3 | 5 |
| 4 | `4 * 4 > 5`, loop ends | 5 |
| end | `n > 1` so print 5 | |

**Complexity:** O(√n).
**Note:** The final `if (n > 1)` is the most common thing people forget.

---

## 23. Decimal ↔ Binary Conversion

**Logic:**
- Decimal → binary: repeatedly divide by 2, collect remainders, read them **bottom to top**.
- Binary → decimal: multiply each bit by its place value (1, 2, 4, 8, ...).

```cpp
string decimalToBinary(int n) {
    if (n == 0) return "0";
    string bin = "";
    while (n > 0) {
        bin = char('0' + n % 2) + bin;   // put new bit at the front
        n /= 2;
    }
    return bin;
}

long long binaryToDecimal(long long b) {
    long long dec = 0, place = 1;
    while (b > 0) {
        dec += (b % 10) * place;
        place *= 2;
        b /= 10;
    }
    return dec;
}
// decimalToBinary(13) -> "1101", binaryToDecimal(1101) -> 13
```

**Dry run: decimalToBinary(13)**

| n | n % 2 | bin |
|---|-------|-----|
| 13 | 1 | 1 |
| 6 | 0 | 01 |
| 3 | 1 | 101 |
| 1 | 1 | 1101 |

**Complexity:** O(log n).
**Note:** `'0' + n % 2` converts the digit 0 or 1 into the character `'0'` or `'1'`. This is explicit type conversion in action.

---

# 🔵 Level 4: Series

## 24. Fibonacci Series

**Logic:** each term is the sum of the previous two. Start with 0 and 1.

```cpp
void fibonacci(int n) {
    long long a = 0, b = 1;
    for (int i = 0; i < n; i++) {
        cout << a << " ";
        long long next = a + b;
        a = b;
        b = next;
    }
    cout << endl;
}
// fibonacci(8) -> 0 1 1 2 3 5 8 13
```

**Dry run (n = 6):**

| i | a (printed) | b | next |
|---|-------------|---|------|
| 0 | 0 | 1 | 1 |
| 1 | 1 | 1 | 2 |
| 2 | 1 | 2 | 3 |
| 3 | 2 | 3 | 5 |
| 4 | 3 | 5 | 8 |
| 5 | 5 | 8 | 13 |

**Complexity:** O(n) time, O(1) space.
**Note:** `int` overflows after the 46th term, so use `long long`.

---

## 25. Sum of Series 1 + 1/2 + 1/3 + ... + 1/n

**Logic:** the type conversion trap: `1 / i` is integer division. Use `1.0 / i`.

```cpp
double harmonicSum(int n) {
    double sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += 1.0 / i;          // 1.0 forces decimal division
    }
    return sum;
}
// harmonicSum(4) -> 2.08333
```

**Dry run (n = 4):** 1 + 0.5 + 0.3333 + 0.25 = **2.0833**.
**Complexity:** O(n).
**Note:** If you wrote `1 / i`, every term except `i = 1` would become `0`.

---

# 🟣 Level 5: Characters

## 26. Character Classification

**Logic:** characters are stored as ASCII numbers, so you can compare them with `>=` and `<=`.

```cpp
void classify(char c) {
    if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') {
        char lower = (c >= 'A' && c <= 'Z') ? c + 32 : c;
        if (lower == 'a' || lower == 'e' || lower == 'i' ||
            lower == 'o' || lower == 'u')
            cout << "Vowel\n";
        else
            cout << "Consonant\n";
    } else if (c >= '0' && c <= '9') {
        cout << "Digit\n";
    } else {
        cout << "Special character\n";
    }
}
// 'E' -> Vowel, 'z' -> Consonant, '5' -> Digit, '#' -> Special character
```

**Dry run ('E'):** it is in `'A'..'Z'` → lower = `'E' + 32 = 'e'` → matches vowel list.
**Complexity:** O(1).
**Key ASCII values:** `'0' = 48`, `'A' = 65`, `'a' = 97`. The difference between a lowercase and uppercase letter is **32**.

---

## 27. Case Conversion Using ASCII

```cpp
char toUpper(char c) {
    if (c >= 'a' && c <= 'z') return c - 'a' + 'A';
    return c;
}

char toLower(char c) {
    if (c >= 'A' && c <= 'Z') return c - 'A' + 'a';
    return c;
}

int charToDigit(char c) {            // '7' -> 7
    return c - '0';
}
// toUpper('g') -> 'G', toLower('Q') -> 'q', charToDigit('7') -> 7
```

**Dry run (toUpper('g')):** `'g' - 'a' = 6`, then `6 + 'A'` = 71 = `'G'`.
**Complexity:** O(1).
**Note:** `c - '0'` is how you turn a digit character into a number. It appears in many string and digit problems.

---

# 📊 Complexity Summary

| # | Program | Time | Space |
|---|---------|------|-------|
| 1-8 | Basic number programs | O(1) to O(n) | O(1) |
| 10-16 | Digit programs | O(log₁₀ n) | O(1) |
| 17 | Prime check | O(√n) | O(1) |
| 19 | GCD (Euclid) | O(log(min(a, b))) | O(1) |
| 22 | Prime factorization | O(√n) | O(1) |
| 23 | Decimal to binary | O(log n) | O(log n) for the string |
| 24 | Fibonacci (n terms) | O(n) | O(1) |

---

# 🏋️ Practice Problems (Try Without Looking)

### 🟢 Easy
- Print all numbers from 1 to n that are divisible by 3 or 5.
- Count how many even and odd digits a number has.
- Find the sum of all even numbers from 1 to n.
- Print the first n odd numbers.
- Check if a number is a power of 2.

### 🟡 Medium
- Check whether a number is a **strong number** (`145 = 1! + 4! + 5!`).
- Find the **sum of first and last digit** of a number.
- Check if the digits of a number are in strictly increasing order.
- Find the **LCM of three numbers**.
- Print all **Armstrong numbers** between 1 and 1000.
- Check if a number is a **perfect square** without using `sqrt()`.

### 🟠 Hard
- Print all **twin primes** (primes differing by 2) up to n.
- Check if a number is a **Harshad number** (divisible by its digit sum).
- Find the **nth Fibonacci number** that is also even.
- Convert a number from **any base to decimal** (base 2 to 16).
- Print the **prime factorization** with powers, e.g. `60 = 2^2 x 3^1 x 5^1`.

---

# ⚠️ Common Mistakes Cheat Sheet

| Mistake | Fix |
|---------|-----|
| `1 / i` gives 0 | Use `1.0 / i` |
| `int` overflow in factorial, power, product | Use `long long` and cast before multiplying |
| Loop destroys the original number | Work on a copy (`temp`) |
| `n = 0` gives wrong digit count | Handle `0` as a special case |
| Forgetting `n > 1` check after prime factorization loop | Add `if (n > 1) cout << n;` |
| Treating `1` as prime | Return `false` for `n < 2` |
| `n % 2 == 1` fails for negatives | Use `n % 2 != 0` or `n % 2 == 0` |
| Using `pow()` for exact integers | Use a loop |
| Off-by-one in loops (`<` vs `<=`) | Dry run with the smallest input |

---

# ✅ Quick Revision Checklist
- [ ] I can extract, count, sum, reverse and compare digits of a number
- [ ] I can check prime, palindrome, Armstrong and perfect numbers
- [ ] I can compute GCD with Euclid's algorithm and LCM from it
- [ ] I can find factors and prime factors
- [ ] I can convert between decimal and binary
- [ ] I can generate Fibonacci terms with only a few variables
- [ ] I know when to use `long long` and `1.0 /` to avoid type conversion bugs
- [ ] I can use ASCII values to classify and convert characters
