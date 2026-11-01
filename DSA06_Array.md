# 📙 Arrays in C++

> An array stores many values of the **same type** in **continuous memory**, accessed by **index**.

## 📑 Contents
1. [Concept & Memory](#1-concept--memory)
2. [Declaration & Initialization](#2-declaration--initialization)
3. [Access & Out of Bounds](#3-access--out-of-bounds)
4. [Traversal & Size](#4-traversal--size)
5. [Arrays in Functions](#5-arrays-in-functions)
6. [Basic Operations](#6-basic-operations)
7. [Insert & Delete](#7-insert--delete)
8. [Reverse (Two Pointers)](#8-reverse-two-pointers)
9. [Frequency Array](#9-frequency-array)
10. [Prefix Sum](#10-prefix-sum)
11. [Binary Search](#11-binary-search)
12. [2D Arrays](#12-2d-arrays)
13. [Mistakes, Practice & Checklist](#13-mistakes-practice--checklist)

---

## 1. Concept & Memory

### 💡 Concept
One name, many values, picked by position (index).

```
Index:    0     1     2     3     4
        +-----+-----+-----+-----+-----+
marks:  | 80  | 65  | 90  | 72  | 88  |
        +-----+-----+-----+-----+-----+
Address: 1000  1004  1008  1012  1016   (int = 4 bytes)
```

`address of arr[i] = base + i × sizeof(type)`, so access is **O(1)**. Indexing starts at 0 because the index is the *offset* from the start.

### 💻 Code
```cpp
int marks[5] = {80, 65, 90, 72, 88};
cout << marks[0];            // 80 (first)
cout << marks[4];            // 88 (last)
cout << *(marks + 2);        // 90, same as marks[2]
```

### ⏰ Complexity
Access: **O(1)**

### ⚠️ Interview Notes
- `arr[i]` is the same as `*(arr + i)`.
- Fixed size, same type, contiguous. That is why access is fast but insertion is costly.

---

## 2. Declaration & Initialization

### 💻 Code
```cpp
int a[5];                    // local: garbage values
int b[5] = {1, 2, 3, 4, 5};
int c[5] = {1, 2};           // {1, 2, 0, 0, 0}
int d[5] = {0};              // all zeros
int e[] = {7, 8, 9};         // size deduced = 3
const int N = 100;
int big[N];                  // size must be a constant
```

### ⚠️ Interview Notes
- Local arrays are **not** zeroed. Global arrays are.
- `int d[5] = {1};` gives `{1, 0, 0, 0, 0}`, not all ones.
- Declare very large arrays (about 10⁶) **globally** to avoid stack overflow.

---

## 3. Access & Out of Bounds

### 💻 Code
```cpp
int arr[5] = {10, 20, 30, 40, 50};
arr[2] = 99;                 // update
arr[0] += 5;                 // 15
int last = arr[4];           // last index = size - 1
// arr[5] = 1;               // DANGER: out of bounds
```

### 🔍 Dry Run

| Statement | Array |
|-----------|-------|
| start | 10 20 30 40 50 |
| `arr[2] = 99` | 10 20 **99** 40 50 |
| `arr[0] += 5` | **15** 20 99 40 50 |

### ⚠️ Interview Notes
- Valid indexes: **0 to n − 1**. C++ does **not** check bounds, so `arr[5]` is undefined behavior (garbage or crash).

---

## 4. Traversal & Size

### 💻 Code
```cpp
int arr[] = {4, 8, 15, 16, 23, 42};
int n = sizeof(arr) / sizeof(arr[0]);     // 24 bytes / 4 = 6

for (int i = 0; i < n; i++) cout << arr[i] << " ";     // forward
for (int i = n - 1; i >= 0; i--) cout << arr[i] << " "; // backward
for (int x : arr) cout << x << " ";                     // range-based (read)
for (int &x : arr) x *= 2;                              // range-based (modify)

// Input
int m, a[100];
cin >> m;
for (int i = 0; i < m; i++) cin >> a[i];
```

### ⏰ Complexity
Traversal: **O(n)**, extra space **O(1)**

### ⚠️ Interview Notes
- `sizeof` trick works **only where the array is declared**, not inside a function.
- Range-based `for` visits the whole declared size, so use it only on fully filled arrays.

---

## 5. Arrays in Functions

### 💡 Concept
An array is passed as the **address of its first element** (no copy). So:
- changes inside the function **modify the original**
- the function doesn't know the size, so pass `n` too

### 💻 Code
```cpp
void print(const int arr[], int n) {          // const = read only
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
}

void doubleAll(int arr[], int n) {
    for (int i = 0; i < n; i++) arr[i] *= 2;  // changes the original
}

int main() {
    int a[] = {1, 2, 3, 4};
    doubleAll(a, 4);
    print(a, 4);                              // 2 4 6 8
}
```

### ⚠️ Interview Notes
- `int arr[]`, `int *arr` and `int arr[100]` are identical as parameters.
- `sizeof(arr)` inside the function gives the **pointer** size, not the array size.
- An array cannot be returned from a function. Modify it in place or use `vector`.

---

## 6. Basic Operations

### 💡 Concept
Most array problems = one loop + a variable that remembers something (sum, best so far, count).

### 💻 Code
```cpp
#include <climits>

long long sumArray(const int a[], int n) {
    long long s = 0;
    for (int i = 0; i < n; i++) s += a[i];
    return s;
}

int maxElement(const int a[], int n) {
    int mx = a[0];                            // not 0 (array may be negative)
    for (int i = 1; i < n; i++)
        if (a[i] > mx) mx = a[i];
    return mx;
}

int linearSearch(const int a[], int n, int key) {
    for (int i = 0; i < n; i++)
        if (a[i] == key) return i;
    return -1;
}

int secondLargest(const int a[], int n) {
    int first = INT_MIN, second = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (a[i] > first)                    { second = first; first = a[i]; }
        else if (a[i] > second && a[i] != first) second = a[i];
    }
    return second;
}
```
Min and count work the same way: change the comparison (`<`) or increment a counter.

### 🔍 Dry Run: `secondLargest({4, 9, 1, 7, 3})`

| a[i] | first | second |
|------|-------|--------|
| 4 | 4 | -∞ |
| 9 | 9 | 4 |
| 1 | 9 | 4 |
| 7 | 9 | 7 |
| 3 | 9 | 7 |

### ⏰ Complexity
All: **O(n)** time, **O(1)** space

### ⚠️ Interview Notes
- Initialize max with `a[0]` or `INT_MIN`, never `0`.
- Use `long long` for sums.

---

## 7. Insert & Delete

### 💡 Concept
Elements are contiguous, so insert and delete need **shifting**.

```
Insert 25 at index 2:   10 20 30 40 __   ->   10 20 25 30 40   (shift right, from the END)
Delete index 1:         10 20 30 40      ->   10 30 40         (shift left, from the position)
```

### 💻 Code
```cpp
bool insertAt(int a[], int &n, int cap, int pos, int val) {
    if (n >= cap || pos < 0 || pos > n) return false;
    for (int i = n; i > pos; i--) a[i] = a[i - 1];   // shift right
    a[pos] = val;
    n++;
    return true;
}

bool deleteAt(int a[], int &n, int pos) {
    if (pos < 0 || pos >= n) return false;
    for (int i = pos; i < n - 1; i++) a[i] = a[i + 1]; // shift left
    n--;
    return true;
}
```

### 🔍 Dry Run: insert 25 at index 2 in `{10, 20, 30, 40}`

| Step | Array |
|------|-------|
| `a[4] = a[3]` | 10 20 30 40 **40** |
| `a[3] = a[2]` | 10 20 30 **30** 40 |
| `a[2] = 25` | 10 20 **25** 30 40 |

### ⏰ Complexity
Middle: **O(n)**, at the end: **O(1)**

### ⚠️ Interview Notes
- Insert shifts from the **end**; delete shifts from the **position**. Wrong direction overwrites data.
- `n` is passed by reference because the size changes.

---

## 8. Reverse (Two Pointers)

### 💡 Concept
One pointer at each end. Swap, then move both inward until they meet.

```
1 2 3 4 5   ->   5 2 3 4 1   ->   5 4 3 2 1
L       R         L   R
```

### 💻 Code
```cpp
void reverseArray(int a[], int n) {
    int l = 0, r = n - 1;
    while (l < r) {
        swap(a[l], a[r]);
        l++;
        r--;
    }
}

bool isPalindrome(const int a[], int n) {
    int l = 0, r = n - 1;
    while (l < r) {
        if (a[l] != a[r]) return false;
        l++;
        r--;
    }
    return true;
}
```

### ⏰ Complexity
**O(n)** time, **O(1)** space

### ⚠️ Interview Notes
- Condition is `l < r`; the middle element of an odd-length array stays.
- Arrays can't be copied with `b = a` or compared with `==`. Use a loop.
- Two pointers is a key pattern, reused in sorted-array and string problems.

---

## 9. Frequency Array

### 💡 Concept
When values lie in a **small range**, use the value as an **index** of a counting array.

### 💻 Code
```cpp
int a[] = {1, 3, 2, 3, 3, 1};
int freq[10] = {0};
for (int i = 0; i < 6; i++) freq[a[i]]++;     // 1->2, 2->1, 3->3

// Letters of a word
char w[] = "hello";
int cnt[26] = {0};
for (int i = 0; w[i] != '\0'; i++) cnt[w[i] - 'a']++;   // l -> 2
```

### 🔍 Dry Run: `{1, 3, 2, 3, 3, 1}`

| a[i] | freq changes |
|------|--------------|
| 1 | freq[1] = 1 |
| 3 | freq[3] = 1 |
| 2 | freq[2] = 1 |
| 3 | freq[3] = 2 |
| 3 | freq[3] = 3 |
| 1 | freq[1] = 2 |

### ⏰ Complexity
**O(n + range)** time, **O(range)** space (replaces an O(n²) nested count)

### ⚠️ Interview Notes
- `w[i] - 'a'` maps `'a'..'z'` to `0..25`.
- Fails for large or negative values. Use a hash map then.

---

## 10. Prefix Sum

### 💡 Concept
Precompute running totals so any range sum is **O(1)**.

```
arr:     3  1  4  1  5  9
prefix:  3  4  8  9 14 23
sum[l..r] = prefix[r] - prefix[l-1]
```

### 💻 Code
```cpp
int a[] = {3, 1, 4, 1, 5, 9};
long long pre[6];
pre[0] = a[0];
for (int i = 1; i < 6; i++) pre[i] = pre[i - 1] + a[i];

int l = 2, r = 4;
long long sum = (l == 0) ? pre[r] : pre[r] - pre[l - 1];   // 14 - 4 = 10
```

### ⏰ Complexity
Build **O(n)**, each query **O(1)**

### ⚠️ Interview Notes
- Handle `l == 0` separately, or use a prefix array of size `n + 1` with `pre[0] = 0`.

---

## 11. Binary Search

### 💡 Concept
On a **sorted** array, compare with the middle and discard half each step.

### 💻 Code
```cpp
int binarySearch(const int a[], int n, int key) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;     // avoids overflow
        if (a[mid] == key)      return mid;
        else if (a[mid] < key)  low = mid + 1;
        else                    high = mid - 1;
    }
    return -1;
}
```

### 🔍 Dry Run: key = 23 in `{2, 5, 8, 12, 16, 23, 38}`

| low | high | mid | a[mid] | Decision |
|-----|------|-----|--------|----------|
| 0 | 6 | 3 | 12 | go right, `low = 4` |
| 4 | 6 | 5 | 23 | found, return 5 |

### ⏰ Complexity
**O(log n)** time, **O(1)** space (about 20 steps for 10⁶ elements)

### ⚠️ Interview Notes
- Works only on sorted data.
- Use `low <= high`, not `<`.

---

## 12. 2D Arrays

### 💡 Concept
A table of rows and columns, `type name[rows][cols]`, stored **row by row** in memory.

```
mat[1][2] = 7
         c0  c1  c2  c3
   r0 |  1   2   3   4 |
   r1 |  5   6   7   8 |
   r2 |  9  10  11  12 |
```

### 💻 Code
```cpp
int mat[3][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};

for (int i = 0; i < 3; i++) {              // traversal + row sums
    int rowSum = 0;
    for (int j = 0; j < 4; j++) {
        cout << mat[i][j] << " ";
        rowSum += mat[i][j];
    }
    cout << "| sum = " << rowSum << "\n";   // 10, 26, 42
}

int sq[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
int diag = 0;
for (int i = 0; i < 3; i++) diag += sq[i][i];          // 15

for (int i = 0; i < 3; i++)                            // transpose
    for (int j = i + 1; j < 3; j++)
        swap(sq[i][j], sq[j][i]);
```

### 🔍 Dry Run: transpose

| (i, j) | Matrix after |
|--------|--------------|
| (0,1) | 1 4 3 / 2 5 6 / 7 8 9 |
| (0,2) | 1 4 7 / 2 5 6 / 3 8 9 |
| (1,2) | 1 4 7 / 2 5 8 / 3 6 9 |

### ⏰ Complexity
**O(rows × cols)** time, **O(1)** extra space

### ⚠️ Interview Notes
- Passing to a function needs the column size: `void f(int a[][4], int rows)`.
- Transpose loops only `j > i`; swapping every pair undoes itself.
- Row-wise traversal is faster than column-wise (row-major memory).

---

## 13. Mistakes, Practice & Checklist

### ⚠️ Common Mistakes

| Mistake | Fix |
|---------|-----|
| Accessing `arr[n]` | Last index is `n - 1` |
| Uninitialized local array | Use `= {0}` |
| `sizeof(arr)` in a function | Pass `n` |
| `max = 0` with negatives | Start with `arr[0]` or `INT_MIN` |
| Copying with `b = a` | Loop over elements |
| Insert from the front | Shift from the end |
| Binary search on unsorted data | Sort first |
| Sum in `int` | Use `long long` |

### 🏋️ Practice
- 🟢 Count positive, negative and zero elements; check if sorted; average as a decimal.
- 🟡 Move zeros to the end; remove duplicates from a sorted array; missing number in 1..n; merge two sorted arrays; rotate by k (reverse three times).
- 🟠 Kadane's maximum subarray; two-sum in a sorted array; sort 0s, 1s, 2s; equilibrium index.

### ✅ Checklist
- [ ] I can explain array memory layout and why access is O(1)
- [ ] I know indexes run 0 to n − 1 and what out of bounds does
- [ ] I can find the size with `sizeof` and know when it fails
- [ ] I know why a function changes the original array
- [ ] I can do sum, max, min, search in one loop
- [ ] I can insert and delete by shifting
- [ ] I can use two pointers, a frequency array and prefix sum
- [ ] I can write binary search without bugs
- [ ] I can traverse and transpose a 2D array
