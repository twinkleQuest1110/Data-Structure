# DSA09 - Matrix & Pointers in 2D Arrays

## Table of Contents
1. [Diagonal Sum](#1-diagonal-sum)
2. [Spiral Matrix](#2-spiral-matrix)
3. [Search in a Row-Column Sorted Matrix](#3-search-in-a-row-column-sorted-matrix)
4. [Pointers & 2D Arrays](#4-pointers--2d-arrays)
5. [Passing a 2D Array to a Function](#5-passing-a-2d-array-to-a-function)
6. [Quick Cheat Sheet](#6-quick-cheat-sheet)

---

## 1. Diagonal Sum

**Problem:** Find the sum of both diagonals of an `n x n` matrix. If `n` is odd, the centre element lies on both diagonals, so count it only once.

```
1 2 3
4 5 6      primary   : 1 + 5 + 9
7 8 9      secondary : 3 + 5 + 7   (5 counted once)

Answer = 1 + 5 + 9 + 3 + 7 = 25
```

### Approach 1 - Brute force `O(n*n)`
Visit every cell and add it if it is on a diagonal.
- Primary diagonal: `i == j`
- Secondary diagonal: `j == n - i - 1`

```cpp
for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        if (i == j) {
            s1 += m[i][j];
        } else if (j == n - i - 1) {
            s1 += m[i][j];
        }
    }
}
```

### Approach 2 - Optimized `O(n)`
We already know where the diagonal cells are, so there is no need to scan the whole matrix. Visit one cell per row for each diagonal.

```cpp
#include <iostream>
using namespace std;

void digsum(int m[][3], int n) {
    int s1 = 0;
    for (int i = 0; i < n; i++) {
        s1 += m[i][i];              // primary diagonal
        if (i != n - 1 - i) {       // skip centre so it is not added twice
            s1 += m[i][n - i - 1];  // secondary diagonal
        }
    }
    cout << s1;
}

int main() {
    int x[3][3] = {{1, 2, 3},
                   {4, 5, 6},
                   {7, 8, 9}};
    digsum(x, 3);   // 25
    return 0;
}
```

| Approach | Time | Space |
|----------|------|-------|
| Brute force | O(n^2) | O(1) |
| Optimized | O(n) | O(1) |

> **Key idea:** If the position of the answer is known by a formula, don't search for it.

---

## 2. Spiral Matrix

**Problem:** Print a matrix in spiral order (clockwise, starting from the top-left).

```
 1   2   3   4
 5   6   7   8
 9  10  11  12
13  14  15  16
17  18  19  20

Output: 1 2 3 4 8 12 16 20 19 18 17 13 9 5 6 7 11 15 14 10
```

### Idea - Peel the matrix layer by layer
Keep 4 boundaries and shrink them after each full loop.

| Variable | Meaning |
|----------|---------|
| `sr` | start row |
| `er` | end row |
| `sc` | start column |
| `ec` | end column |

Each layer has 4 moves:
1. **Left to right** - top row `x[sr][sc..ec]`
2. **Top to bottom** - right column `x[sr+1..er][ec]`
3. **Right to left** - bottom row `x[er][ec-1..sc]`
4. **Bottom to top** - left column `x[er-1..sr+1][sc]`

Then `sr++, sc++, er--, ec--`.

```cpp
#include <iostream>
using namespace std;

void spi(int x[][4], int n, int m) {
    int sr = 0, sc = 0;
    int er = n - 1;
    int ec = m - 1;

    while (sr <= er && sc <= ec) {

        // left to right
        for (int j = sc; j <= ec; j++) {
            cout << x[sr][j] << " ,";
        }

        // top to bottom
        for (int i = sr + 1; i <= er; i++) {
            cout << x[i][ec] << " ,";
        }

        // right to left
        for (int j = ec - 1; j >= sc; j--) {
            if (sr == er) break;        // only one row left, already printed
            cout << x[er][j] << " ,";
        }

        // bottom to top
        for (int i = er - 1; i >= sr + 1; i--) {
            if (sc == ec) break;        // only one column left, already printed
            cout << x[i][sc] << " ,";
        }

        sr++; sc++;
        er--; ec--;
    }
}

int main() {
    int x[5][4] = {{1,  2,  3,  4},
                   {5,  6,  7,  8},
                   {9,  10, 11, 12},
                   {13, 14, 15, 16},
                   {17, 18, 19, 20}};
    spi(x, 5, 4);
    return 0;
}
```

### Things to be careful about
- The loop condition must be `sr <= er && sc <= ec` (rows are compared with rows, columns with columns).
- The two `break` checks are **required** for non-square matrices. Without them, when only one row or one column is left, the last two loops print elements again.
- The function must be closed with `}` before `main()`.

**Time:** O(n*m) - every element is visited once. **Space:** O(1).

---

## 3. Search in a Row-Column Sorted Matrix

**Problem:** Every row is sorted left to right and every column is sorted top to bottom. Find `key`.

```
 1   2   3   4
 5   6   7   8
 9  10  11  12
13  14  15  16
```

### Staircase Search
Start from the **top-right corner** (row `0`, column `m-1`).

| Compare `key` with current | Action | Why |
|---|---|---|
| `key == current` | found | - |
| `key < current` | `c--` (go left) | everything below in this column is bigger |
| `key > current` | `r++` (go down) | everything to the left in this row is smaller |

Each step removes one full row or one full column.

```cpp
#include <iostream>
using namespace std;

bool findi(int x[][4], int n, int m, int key) {
    int r = 0;
    int c = m - 1;

    while (r < n && c >= 0) {
        int st = x[r][c];

        if (key == st) {
            cout << "FOUND at :" << r << "," << c;
            return true;
        } else if (key < st) {
            c--;
        } else {
            r++;
        }
    }
    return false;
}

int main() {
    int x[4][4] = {{1,  2,  3,  4},
                   {5,  6,  7,  8},
                   {9,  10, 11, 12},
                   {13, 14, 15, 16}};
    findi(x, 4, 4, 11);   // FOUND at :2,2
    return 0;
}
```

### Dry run for `key = 11`
```
(0,3) = 4   -> 11 > 4   -> go down
(1,3) = 8   -> 11 > 8   -> go down
(2,3) = 12  -> 11 < 12  -> go left
(2,2) = 11  -> FOUND
```

| Approach | Time |
|----------|------|
| Linear scan | O(n*m) |
| Staircase search | **O(n + m)** |

> Starting from the **bottom-left** corner works too. Starting from top-left or bottom-right does not, because both moves would increase (or both decrease) the value.

---

## 4. Pointers & 2D Arrays

### Memory layout
A 2D array is stored in memory as one continuous block, **row after row** (row-major order).

```
int x[4][4]

address:  100  104  108  112 | 116  120  124  128 | 132 ...
value:      1    2    3    4 |   5    6    7    8 |   9 ...
            \_____ row 0 ___/  \_____ row 1 ___/
```

### `x` is a pointer to a ROW
`x` decays to `int (*)[4]`, which means "pointer to an array of 4 ints". So one step of `x + 1` jumps over a **whole row**, not a single element.

```cpp
#include <iostream>
using namespace std;

int main() {
    int x[4][4] = {{1,  2,  3,  4},
                   {5,  6,  7,  8},
                   {9,  10, 11, 12},
                   {13, 14, 15, 16}};

    cout << x     << " = "  << &x[0][0] << endl;  // same address (start of row 0)
    cout << x     << " != " << &x[0][1] << endl;  // differs by 4 bytes
    cout << x + 1 << " = "  << &x[1][0] << endl;  // start of row 1 (+16 bytes)
    return 0;
}
```

### Pointer arithmetic table

| Expression | Type | Meaning |
|------------|------|---------|
| `x` | `int (*)[4]` | address of row 0 |
| `x + 1` | `int (*)[4]` | address of row 1 (jumps 4 ints = 16 bytes) |
| `*x` or `x[0]` | `int*` | address of element `[0][0]` (row 0 decays to a pointer) |
| `*(x + i)` or `x[i]` | `int*` | address of the first element of row `i` |
| `*(x + i) + j` | `int*` | address of element `[i][j]` |
| `*(*(x + i) + j)` | `int` | **value** of element `[i][j]` |

```
x[i][j]  ==  *(*(x + i) + j)
```

### Step-by-step for `*(*(x + 1) + 2)`
```
x            -> row 0
x + 1        -> row 1           (move 1 row)
*(x + 1)     -> first element of row 1 (int*)
*(x + 1) + 2 -> move 2 elements -> &x[1][2]
*( ... )     -> value at x[1][2] = 7
```

> **Remember:** `x + 1` moves by one row, `*x + 1` moves by one element.

---

