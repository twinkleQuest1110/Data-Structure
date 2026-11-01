# 📕Pointers in C++

> A pointer is a variable that stores the **memory address** of another variable.

## 📑 Contents
1. [Concept & Memory](#1-concept--memory)
2. [Declaration, Initialization & nullptr](#2-declaration-initialization--nullptr)
3. [Dereferencing](#3-dereferencing)
4. [Pointer Arithmetic](#4-pointer-arithmetic)
5. [Pointers & Arrays](#5-pointers--arrays)
6. [Pointers & Functions](#6-pointers--functions)
7. [Pointer to Pointer](#7-pointer-to-pointer)
8. [const with Pointers](#8-const-with-pointers)
9. [Dynamic Memory (new / delete)](#9-dynamic-memory-new--delete)
10. [Pointer vs Reference](#10-pointer-vs-reference)
11. [Mistakes, Practice & Checklist](#11-mistakes-practice--checklist)

---

## 1. Concept & Memory

### 💡 Concept
Every variable lives at an **address** in memory. A pointer holds that address.

```
   x                      p
+--------+            +--------+
|   10   |  <---------| 0x1000 |
+--------+            +--------+
 0x1000                 0x2000

x  = 10        (value)
&x = 0x1000    (address of x)
p  = 0x1000    (p stores the address of x)
*p = 10        (value at that address)
```

| Symbol | Name | Meaning |
|--------|------|---------|
| `&x` | address-of | address of variable `x` |
| `*p` | dereference | value stored at the address in `p` |
| `int *p` | declaration | `p` is a pointer to an `int` |

### 💻 Code
```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 10;
    int *p = &x;                 // p stores the address of x

    cout << x << endl;           // 10
    cout << &x << endl;          // address of x
    cout << p << endl;           // same address
    cout << *p << endl;          // 10
    cout << &p << endl;          // the pointer itself has its own address
    return 0;
}
```

### ⏰ Complexity
Access through a pointer: **O(1)**

### ⚠️ Interview Notes
- `sizeof(p)` is **8 bytes** on a 64-bit system (4 on 32-bit), whatever the pointed-to type is.
- The `*` in a declaration means "pointer to"; the `*` in an expression means "value at".

---

## 2. Declaration, Initialization & nullptr

### 💻 Code
```cpp
int x = 5;
int *p = &x;                // points to x
int *q = nullptr;           // points to nothing (safe default)
int *r;                     // BAD: uninitialized, holds a garbage address

int *a, *b;                 // both are pointers
int *c, d;                  // c is a pointer, d is a plain int

if (q == nullptr) cout << "q is null\n";
if (p) cout << "p is valid\n";       // non-null pointer is true
```

### ⚠️ Interview Notes
- Always initialize pointers: to a valid address or `nullptr`.
- Use `nullptr` (C++11), not `NULL` or `0`.
- Pointer type must match the data type: `int*` for `int`, `double*` for `double`.

---

## 3. Dereferencing

### 💡 Concept
`*p` is the variable itself, not a copy. Reading or writing through `*p` reads or writes the original.

### 💻 Code
```cpp
int x = 10;
int *p = &x;

*p = 20;                     // changes x
cout << x << endl;           // 20

*p += 5;                     // x = 25
(*p)++;                      // x = 26 (brackets needed)
cout << x << endl;           // 26
```

### 🔍 Dry Run

| Statement | x | *p |
|-----------|---|----|
| `p = &x` | 10 | 10 |
| `*p = 20` | 20 | 20 |
| `*p += 5` | 25 | 25 |
| `(*p)++` | 26 | 26 |

### ⚠️ Interview Notes
- `*p++` increments the **pointer** (then dereferences); `(*p)++` increments the **value**.
- Dereferencing `nullptr` or an uninitialized pointer crashes the program (segmentation fault).

---

## 4. Pointer Arithmetic

### 💡 Concept
Adding 1 to a pointer moves it by **`sizeof(type)` bytes**, to the next element, not the next byte.

```
int *p = 1000      p + 1 = 1004      p + 2 = 1008     (int = 4 bytes)
double *d = 2000   d + 1 = 2008                         (double = 8 bytes)
```

### 💻 Code
```cpp
int arr[4] = {10, 20, 30, 40};
int *p = arr;

cout << *p << endl;          // 10
p++;                         // moves to arr[1]
cout << *p << endl;          // 20
p += 2;                      // moves to arr[3]
cout << *p << endl;          // 40
p--;                         // back to arr[2]
cout << *p << endl;          // 30

int *start = arr, *end = arr + 3;
cout << end - start << endl; // 3 (number of elements between them)
```

### 🔍 Dry Run

| Statement | p points to | *p |
|-----------|-------------|----|
| `p = arr` | arr[0] | 10 |
| `p++` | arr[1] | 20 |
| `p += 2` | arr[3] | 40 |
| `p--` | arr[2] | 30 |

### ⚠️ Interview Notes
- Valid operations: `p + n`, `p - n`, `p++`, `p--`, `p2 - p1`, comparisons.
- **Not valid:** adding two pointers, multiplying or dividing pointers.
- Going outside the array is undefined behavior.

---

## 5. Pointers & Arrays

### 💡 Concept
An array name is (almost) a pointer to its first element.

`arr[i]` ≡ `*(arr + i)` ≡ `p[i]` (when `p = arr`)

### 💻 Code
```cpp
int arr[5] = {1, 2, 3, 4, 5};
int *p = arr;                         // same as &arr[0]

for (int i = 0; i < 5; i++)
    cout << *(p + i) << " ";          // 1 2 3 4 5
cout << endl;

for (int *q = arr; q < arr + 5; q++)  // traverse by moving the pointer
    cout << *q << " ";
cout << endl;

// Reverse using two pointers
int *l = arr, *r = arr + 4;
while (l < r) {
    swap(*l, *r);
    l++;
    r--;
}                                     // 5 4 3 2 1
```

### ⏰ Complexity
Traversal: **O(n)**, Space: **O(1)**

### ⚠️ Interview Notes
- **Array vs pointer:** `sizeof(arr)` = whole array (20 bytes); `sizeof(p)` = 8 bytes.
- An array name **cannot be reassigned** (`arr = p` is an error); a pointer can.
- This is why arrays decay to pointers when passed to functions (see Arrays README).

---

## 6. Pointers & Functions

### 💡 Concept
Passing a **pointer** lets a function change the caller's variable. Pass by value would only change a copy.

### 💻 Code
```cpp
void swapPtr(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swapRef(int &a, int &b) {          // reference version (cleaner)
    int temp = a;
    a = b;
    b = temp;
}

int findMax(const int *arr, int n, int *index) {   // "returns" 2 values
    int mx = arr[0];
    *index = 0;
    for (int i = 1; i < n; i++)
        if (arr[i] > mx) { mx = arr[i]; *index = i; }
    return mx;
}

int main() {
    int x = 5, y = 10;
    swapPtr(&x, &y);                     // pass addresses
    cout << x << " " << y << endl;       // 10 5

    int a[] = {3, 9, 4}, idx;
    cout << findMax(a, 3, &idx) << " at " << idx << endl;   // 9 at 1
}
```

### 🔍 Dry Run: `swapPtr(&x, &y)` with x = 5, y = 10

| Step | *a (x) | *b (y) | temp |
|------|--------|--------|------|
| start | 5 | 10 | - |
| `temp = *a` | 5 | 10 | 5 |
| `*a = *b` | 10 | 10 | 5 |
| `*b = temp` | 10 | 5 | 5 |

### ⚠️ Interview Notes
- Pointer parameters let a function **return multiple values**.
- Check `if (ptr == nullptr)` before dereferencing a pointer parameter.
- **Never return the address of a local variable**; it is destroyed when the function ends (dangling pointer).

---

## 7. Pointer to Pointer

### 💡 Concept
A pointer can store the address of **another pointer**.

```
x  = 10     p = &x      pp = &p
**pp = *p = x = 10
```

### 💻 Code
```cpp
int x = 10;
int *p = &x;
int **pp = &p;

cout << x << " " << *p << " " << **pp << endl;   // 10 10 10

**pp = 50;                                       // changes x
cout << x << endl;                               // 50
```

### ⚠️ Interview Notes
- Used for 2D dynamic arrays and for **changing where a pointer points** inside a function.
- Each extra `*` is one more level of indirection.

---

## 8. const with Pointers

### 💡 Concept
Read the declaration **right to left**.

| Declaration | Meaning | Can change value? | Can change address? |
|-------------|---------|-------------------|---------------------|
| `const int *p` | pointer to const int | No (`*p = 1` error) | Yes |
| `int *const p` | const pointer to int | Yes | No (`p = &y` error) |
| `const int *const p` | const pointer to const int | No | No |

### 💻 Code
```cpp
int x = 1, y = 2;

const int *p1 = &x;
// *p1 = 5;          // ERROR: data is const
p1 = &y;             // OK

int *const p2 = &x;
*p2 = 5;             // OK
// p2 = &y;          // ERROR: pointer is const
```

### ⚠️ Interview Notes
- Use `const int *` for function parameters that should only **read** data.
- Trick: `const` applies to what is on its **left**; if nothing, to what is on its right.

---

## 9. Dynamic Memory (new / delete)

### 💡 Concept
- **Stack:** automatic variables; freed when the scope ends; fixed size known at compile time.
- **Heap:** memory you request at runtime with `new`; stays until you `delete` it.

### 💻 Code
```cpp
// Single value
int *p = new int(42);
cout << *p << endl;
delete p;                    // free it
p = nullptr;                 // avoid a dangling pointer

// Dynamic array (size decided at runtime)
int n;
cin >> n;
int *arr = new int[n];
for (int i = 0; i < n; i++) arr[i] = i * i;
for (int i = 0; i < n; i++) cout << arr[i] << " ";
delete[] arr;                // delete[] for arrays
arr = nullptr;

// Dynamic 2D array
int rows = 3, cols = 4;
int **mat = new int*[rows];
for (int i = 0; i < rows; i++) mat[i] = new int[cols]();   // () zero-initializes
for (int i = 0; i < rows; i++) delete[] mat[i];
delete[] mat;
```

### 🔍 Dry Run: `n = 4`

| i | arr[i] |
|---|--------|
| 0 | 0 |
| 1 | 1 |
| 2 | 4 |
| 3 | 9 |

### ⏰ Complexity
Allocation depends on the allocator; the array above uses **O(n)** space.

### ⚠️ Interview Notes
- Every `new` needs exactly one `delete`; every `new[]` needs `delete[]`. Mismatches are undefined behavior.
- Forgetting `delete` = **memory leak**. Deleting twice = crash.
- In modern C++ prefer `vector` and smart pointers (`unique_ptr`, `shared_ptr`) over raw `new` / `delete`.

---

## 10. Pointer vs Reference

| Feature | Pointer | Reference |
|---------|---------|-----------|
| Syntax | `int *p = &x;` | `int &r = x;` |
| Can be null | Yes | No |
| Can be reassigned | Yes | No (bound for life) |
| Must be initialized | No (but should) | Yes |
| Access | `*p` | `r` directly |
| Arithmetic | Yes | No |

```cpp
int x = 10;
int &r = x;       // r is another name for x
r = 20;           // x is now 20
```

**Rule of thumb:** use a reference when the argument must exist; use a pointer when it may be absent (`nullptr`) or you need arithmetic or dynamic memory.

---

## 11. Mistakes, Practice & Checklist

### ⚠️ Common Mistakes

| Mistake | Problem | Fix |
|---------|---------|-----|
| Uninitialized pointer | Garbage address | `int *p = nullptr;` |
| Dereferencing `nullptr` | Segmentation fault | Check `if (p)` first |
| Returning address of a local variable | Dangling pointer | Return by value or use `new` |
| Using memory after `delete` | Dangling pointer | Set `p = nullptr` after `delete` |
| Missing `delete` | Memory leak | Pair every `new` with `delete` |
| `delete` instead of `delete[]` | Undefined behavior | Match `new[]` with `delete[]` |
| `int *a, b;` | `b` is not a pointer | Write `int *a, *b;` |
| `*p++` when you meant `(*p)++` | Moves pointer, not value | Use brackets |

### 🏋️ Practice
- 🟢 Print the value and address of a variable using a pointer; swap two numbers using pointers; print an array using pointer arithmetic.
- 🟡 Find the max and min of an array using only pointers; reverse an array with two pointers; count even elements using a pointer; write `strlen()` using a `char*`.
- 🟠 Allocate an array of size `n` dynamically, sort it, then free it; create a dynamic 2D matrix and transpose it; implement a function that changes a pointer using `int **`.

### ✅ Checklist
- [ ] I can explain `&`, `*` and what a pointer stores
- [ ] I always initialize pointers (or use `nullptr`)
- [ ] I know why `p + 1` moves by `sizeof(type)` bytes
- [ ] I understand `arr[i]` ≡ `*(arr + i)`
- [ ] I can swap and return multiple values using pointers
- [ ] I can read `const int *p` vs `int *const p`
- [ ] I can use `new` / `delete` and `new[]` / `delete[]` correctly
- [ ] I can spot dangling pointers, leaks and null dereferences
- [ ] I know when to use a pointer vs a reference
