# 🔁 Recursion (Part 1) — DSA

A collection of beginner-friendly **recursion** problems and solutions, solved while learning Data Structures & Algorithms. Each problem includes the core idea, the base case, the recursive case, and complexity.

![Language](https://img.shields.io/badge/language-Java-orange)
![Topic](https://img.shields.io/badge/topic-Recursion-blue)
![Status](https://img.shields.io/badge/status-in%20progress-green)

---

## 📚 Table of Contents

- [What is Recursion?](#-what-is-recursion)
- [How Recursion Works in Memory](#-how-recursion-works-in-memory)
- [Topics Covered](#-topics-covered)
- [Problems & Solutions](#-problems--solutions)
- [Complexity Summary](#-complexity-summary)
- [Project Structure](#-project-structure)
- [How to Run](#-how-to-run)
- [Contributing](#-contributing)

---

## 🧠 What is Recursion?

Recursion is a technique where a function **calls itself** to solve a smaller version of the same problem.

Every recursive solution has two parts:

1. **Base case** – the condition that stops the recursion.
2. **Recursive case** – the function calls itself with a smaller input.

```java
void solve(int n) {
    if (n == 0) return;      // base case
    solve(n - 1);            // recursive call
}
```

## 🧩 How Recursion Works in Memory

Each function call is pushed onto the **call stack** as a stack frame. When the base case is hit, frames are popped one by one (LIFO) and results are returned back up.

- Too many calls without a base case → **Stack Overflow** ❌
- Dry running with a call stack helps visualize the flow of execution.

---

## ✅ Topics Covered

- [x] What is Recursion?
- [x] Dive Deep into Recursion
- [x] Recursion in Memory
- [x] Numbers in Decreasing Order
- [x] Dry Run with Call Stack
- [x] Stack Overflow
- [x] Sum of N Natural Numbers
- [x] Nth Fibonacci
- [x] Nth Fibonacci (Code)
- [x] Check if Array is Sorted
- [x] First Occurrence
- [x] Last Occurrence
- [x] Print X to the Power N
- [x] X to the Power N (Code)

---

## 💡 Problems & Solutions

### 1. Print Numbers in Decreasing Order

```java
static void printDec(int n) {
    if (n == 0) return;
    System.out.print(n + " ");
    printDec(n - 1);
}
```
**Time:** O(n) | **Space:** O(n)

### 2. Sum of N Natural Numbers

```java
static int sum(int n) {
    if (n == 1) return 1;
    return n + sum(n - 1);
}
```
**Time:** O(n) | **Space:** O(n)

### 3. Nth Fibonacci Number

```java
static int fib(int n) {
    if (n == 0 || n == 1) return n;
    return fib(n - 1) + fib(n - 2);
}
```
**Time:** O(2ⁿ) | **Space:** O(n)

### 4. Check if Array is Sorted

```java
static boolean isSorted(int[] arr, int i) {
    if (i == arr.length - 1) return true;
    if (arr[i] > arr[i + 1]) return false;
    return isSorted(arr, i + 1);
}
```
**Time:** O(n) | **Space:** O(n)

### 5. First Occurrence of an Element

```java
static int firstOccurrence(int[] arr, int key, int i) {
    if (i == arr.length) return -1;
    if (arr[i] == key) return i;
    return firstOccurrence(arr, key, i + 1);
}
```
**Time:** O(n) | **Space:** O(n)

### 6. Last Occurrence of an Element

```java
static int lastOccurrence(int[] arr, int key, int i) {
    if (i == arr.length) return -1;
    int isFound = lastOccurrence(arr, key, i + 1);
    if (isFound == -1 && arr[i] == key) return i;
    return isFound;
}
```
**Time:** O(n) | **Space:** O(n)

### 7. Print X to the Power N

**Approach 1 – Linear**
```java
static int power(int x, int n) {
    if (n == 0) return 1;
    return x * power(x, n - 1);
}
```
**Time:** O(n) | **Space:** O(n)

**Approach 2 – Optimized (Divide & Conquer)**
```java
static int optimizedPower(int x, int n) {
    if (n == 0) return 1;
    int half = optimizedPower(x, n / 2);
    int halfSq = half * half;
    if (n % 2 != 0) return x * halfSq;
    return halfSq;
}
```
**Time:** O(log n) | **Space:** O(log n)

---

## 📊 Complexity Summary

| Problem                    | Time     | Space    |
| -------------------------- | -------- | -------- |
| Decreasing Order           | O(n)     | O(n)     |
| Sum of N Natural Numbers   | O(n)     | O(n)     |
| Nth Fibonacci              | O(2ⁿ)    | O(n)     |
| Check if Array Sorted      | O(n)     | O(n)     |
| First / Last Occurrence    | O(n)     | O(n)     |
| X to the Power N (linear)  | O(n)     | O(n)     |
| X to the Power N (optimal) | O(log n) | O(log n) |

---

## 📁 Project Structure

```
recursion-dsa/
├── README.md
├── src/
│   ├── DecreasingOrder.java
│   ├── SumOfN.java
│   ├── Fibonacci.java
│   ├── CheckSorted.java
│   ├── FirstOccurrence.java
│   ├── LastOccurrence.java
│   └── PowerXN.java
```

## ▶️ How to Run

```bash
# Clone the repository
git clone https://github.com/<your-username>/recursion-dsa.git
cd recursion-dsa/src

# Compile and run
javac Fibonacci.java
java Fibonacci
```

## 🤝 Contributing

Suggestions and improvements are welcome! Feel free to open an issue or submit a pull request.

## ⭐ Support

If this repo helped you, give it a star!

---

> **Next up:** Recursion (Part 2) — Tiling Problem, Remove Duplicates, Friends Pairing, Binary Strings, and more.
