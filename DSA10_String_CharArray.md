# DSA10 - Strings & Character Arrays

## Table of Contents
1. [Character Arrays Basics](#1-character-arrays-basics)
2. [Taking Input](#2-taking-input)
3. [Convert to Uppercase](#3-convert-to-uppercase)
4. [Palindrome Check](#4-palindrome-check)
5. [Built-in Functions (`<cstring>`)](#5-built-in-functions-cstring)
6. [Common Mistakes](#6-common-mistakes)
7. [Quick Cheat Sheet](#7-quick-cheat-sheet)


---

## 1. Character Arrays Basics

A C-style string is just a `char` array that ends with a **null character** `'\0'`.

```cpp
char word[] = "apple";
```

```
index :   0    1    2    3    4    5
value :  'a'  'p'  'p'  'l'  'e'  '\0'
```

- The array size is **6**, but the string length is **5**.
- `'\0'` marks the end of the string. Functions like `cout` and `strlen` keep reading until they find it.

| Declaration | Size | Length |
|-------------|------|--------|
| `char a[] = "apple";` | 6 | 5 |
| `char a[20] = "apple";` | 20 | 5 |

> Always keep **one extra slot** for `'\0'`.

---

## 2. Taking Input

```cpp
char name[20];

cin >> name;              // stops at the first space  ("hello world" -> "hello")
cin.getline(name, 20);    // reads the full line including spaces
```

| Method | Reads spaces? |
|--------|---------------|
| `cin >> str` | No |
| `cin.getline(str, size)` | Yes |

---

## 3. Convert to Uppercase

**Problem:** Convert every lowercase letter of a word to uppercase.

**Idea:** In ASCII, `'a' - 'A' = 32`. So `ch - 'a' + 'A'` turns `'p'` into `'P'`.

```cpp
#include <iostream>
#include <cstring>
using namespace std;

void upp(char wo[], int n) {
    for (int i = 0; i < n; i++) {
        char ch = wo[i];
        if (ch >= 'A' && ch <= 'Z') {
            continue;                    // already uppercase
        } else {
            wo[i] = ch - 'a' + 'A';      // lowercase -> uppercase
        }
    }
}

int main() {
    char word[] = "apPLe";
    upp(word, strlen(word));
    cout << word;                        // APPLE
    return 0;
}
```

### Safer version
The `else` above also runs for spaces, digits and symbols, and corrupts them. Check for lowercase explicitly.

```cpp
void upp(char wo[], int n) {
    for (int i = 0; i < n; i++) {
        if (wo[i] >= 'a' && wo[i] <= 'z') {
            wo[i] = wo[i] - 'a' + 'A';
        }
    }
}
```

> The built-in `toupper(ch)` from `<cctype>` does the same job.

**Time:** O(n). **Space:** O(1).

---

## 4. Palindrome Check

**Problem:** Check whether a string reads the same forwards and backwards.

**Idea:** Two pointers. One starts at the beginning, one at the end. Compare and move inward. If any pair differs, it is not a palindrome.

```
 o  y     r a c e c a r     y  o
 ^                               ^
st                              end      equal -> move inward
```

```cpp
#include <iostream>
#include <cstring>
using namespace std;

bool isPalindrome(char wo[], int n) {
    int st = 0;
    int end = n - 1;
    while (st < end) {
        if (wo[st] != wo[end]) {
            return false;
        } else {
            st++;
            end--;
        }
    }
    return true;
}

int main() {
    char word[] = "oy racecar yo";
    bool x = isPalindrome(word, strlen(word));
    cout << (x ? "yes" : "no");          // yes
    return 0;
}
```

- Spaces count as characters here. `"oy racecar yo"` works because the spaces are also placed symmetrically.
- The loop stops at `st < end`, so the middle character of an odd-length string never needs a comparison.

**Time:** O(n). **Space:** O(1).

---

## 5. Built-in Functions (`<cstring>`)

```cpp
#include <iostream>
#include <cstring>
using namespace std;

int main() {
    char str1[20];

    // str1 = "Hey Iam aaisha";   // ERROR: arrays cannot be assigned with =
    strcpy(str1, "Hey Iam aaisha");
    cout << str1 << endl;          // Hey Iam aaisha

    char str2[30] = "welcome to hood";
    strcpy(str1, str2);            // copy str2 into str1
    cout << str1 << endl;          // welcome to hood

    // concatenation
    char s1[20] = " yo yo ";
    char s2[20] = "honey singh";
    strcat(s1, s2);                // s2 is added at the end of s1
    cout << s1 << endl;            //  yo yo honey singh
    cout << s2 << endl;            // honey singh (unchanged)

    // comparison
    char s3[20] = "mango";
    char s4[20] = "banana";
    cout << strcmp(s3, s4) << endl;   // positive number
    return 0;
}
```

| Function | What it does | Notes |
|----------|--------------|-------|
| `strlen(s)` | Length without `'\0'` | O(n), it walks the string |
| `strcpy(dest, src)` | Copies `src` into `dest` | `dest` must be big enough |
| `strcat(dest, src)` | Appends `src` to the end of `dest` | `dest` must hold both strings + `'\0'` |
| `strcmp(a, b)` | Compares alphabetically | See table below |

### `strcmp` return values

| Result | Meaning |
|--------|---------|
| `0` | strings are equal |
| negative | `a` comes before `b` |
| positive | `a` comes after `b` |

`"mango"` vs `"banana"`: `'m'` comes after `'b'`, so the result is positive. The exact number depends on the compiler, so only check the **sign**, never a specific value.

---

## 6. Common Mistakes

| Mistake | Problem | Fix |
|---------|---------|-----|
| `str1 = "hello";` | Arrays cannot be assigned | `strcpy(str1, "hello");` |
| `if (a == b)` for two char arrays | Compares **addresses**, not text | `if (strcmp(a, b) == 0)` |
| Destination too small in `strcpy` / `strcat` | Buffer overflow, undefined behaviour | Make sure size >= length + 1 |
| Forgetting `'\0'` space | String runs into garbage memory | Allocate one extra slot |
| `sizeof(word)` instead of `strlen(word)` | `sizeof` gives the array size, not the string length | Use `strlen` |
| `cin >> str` for sentences | Stops at the first space | Use `cin.getline` |

### Size check for `strcat` in the example
```
" yo yo "      -> 7 characters
"honey singh"  -> 11 characters
total          -> 18 + 1 ('\0') = 19  <= 20   OK
```
Add one more character and `s1` would overflow.

---

## 7. Quick Cheat Sheet

| Topic | Remember |
|-------|----------|
| C-string | `char` array ending with `'\0'` |
| Size vs length | size includes `'\0'`, length does not |
| Case conversion | `ch - 'a' + 'A'` (lower to upper), difference is 32 |
| Palindrome | Two pointers `st` and `end`, move inward |
| Copy | `strcpy(dest, src)` |
| Join | `strcat(dest, src)` |
| Compare | `strcmp(a, b)`, `0` means equal |
| Length | `strlen(s)` |
| Input with spaces | `cin.getline(s, size)` |

### Practice Problems
- Reverse a string
- Count vowels and consonants
- Check if two strings are anagrams
- Remove all spaces from a string
- Find the largest word in a sentence
- Count the frequency of each character
