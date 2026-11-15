# DSA11 - OOP Concepts in C++

## Table of Contents
1. [What is OOP?](#1-what-is-oop)
2. [Class & Object](#2-class--object) 
3. [Access Specifiers](#3-access-specifiers)
4. [Constructors](#4-constructors) 
5. [Destructor](#5-destructor) 
6. [`this` Pointer](#6-this-pointer)
7. [Static Members](#7-static-members)
8. [Shallow Copy vs Deep Copy](#8-shallow-copy-vs-deep-copy)
9. [The 4 Pillars of OOP](#9-the-4-pillars-of-oop)
10. [Encapsulation](#10-encapsulation)
11. [Abstraction](#11-abstraction)
12. [Inheritance](#12-inheritance)
13. [Polymorphism](#13-polymorphism)
14. [Common Mistakes](#14-common-mistakes)
15. [Quick Cheat Sheet](#15-quick-cheat-sheet)

---

## 1. What is OOP?

**Object-Oriented Programming** organizes code around **objects** (data + the functions that work on that data) instead of separate functions and variables.

| Procedural (C style) | Object-Oriented (C++) |
|----------------------|-----------------------|
| Focus on functions | Focus on objects |
| Data and functions are separate | Data and functions are bundled together |
| Data is easy to change from anywhere | Data can be protected |
| Hard to scale | Easier to reuse and maintain |

---

## 2. Class & Object

- **Class** is a blueprint (a user-defined data type).
- **Object** is a real instance created from that blueprint.

```
Class  : Student  (name, age, show())
Object : s1 = {"Aaisha", 20}     s2 = {"Rahul", 21}
```

```cpp
#include <iostream>
#include <string>
using namespace std;

class Student {
public:
    string name;     // data members (properties)
    int age;

    void show() {    // member function (behaviour)
        cout << name << " " << age << endl;
    }
};

int main() {
    Student s1;          // object created
    s1.name = "Aaisha";
    s1.age = 20;
    s1.show();           // Aaisha 20
    return 0;
}
```

- Use the **dot** operator `.` with an object: `s1.name`
- Use the **arrow** operator `->` with a pointer to an object: `ptr->name`
- An empty class still has size **1 byte**, so every object has a unique address.

---

## 3. Access Specifiers

| Specifier | Same class | Derived class | Outside the class |
|-----------|:----------:|:-------------:|:-----------------:|
| `public` | yes | yes | yes |
| `protected` | yes | yes | no |
| `private` | yes | no | no |

> In a `class`, members are **private by default**. In a `struct`, they are **public by default**. That is the only difference between them.

---

## 4. Constructors

A **constructor** is a special function that runs **automatically** when an object is created.
- Same name as the class
- No return type (not even `void`)
- Used to initialise data members

```cpp
class Student {
public:
    string name;
    int age;

    // 1. Default constructor
    Student() {
        name = "Unknown";
        age = 0;
    }

    // 2. Parameterized constructor (with initializer list)
    Student(string n, int a) : name(n), age(a) {}

    // 3. Copy constructor
    Student(const Student &other) {
        name = other.name;
        age = other.age;
    }
};

int main() {
    Student a;                    // default
    Student b("Aaisha", 20);      // parameterized
    Student c(b);                 // copy  (c is a copy of b)
    return 0;
}
```

| Type | When it runs |
|------|--------------|
| Default | `Student a;` |
| Parameterized | `Student b("Aaisha", 20);` |
| Copy | `Student c(b);` or `Student c = b;` |

### Notes
- If you write **no** constructor, the compiler gives you a default one (it does not initialise `int`, so you get garbage values).
- If you write **any** constructor, the compiler stops generating the default one.
- The copy constructor takes the parameter **by reference** (`const Student &`). By value would call the copy constructor again, forever.
- **Initializer lists** (`: name(n), age(a)`) are faster than assigning inside the body, and are required for `const` and reference members.

---

## 5. Destructor

A **destructor** runs automatically when an object is destroyed (goes out of scope or is deleted). It is used to release resources such as heap memory.

```cpp
class Demo {
public:
    Demo()  { cout << "Constructor" << endl; }
    ~Demo() { cout << "Destructor"  << endl; }
};

int main() {
    Demo d;
    return 0;
}
// Constructor
// Destructor
```

- Name is `~ClassName`.
- No parameters, no return type, and **only one** per class.
- Objects are destroyed in the **reverse order** of creation.

---

## 6. `this` Pointer

`this` is a hidden pointer that points to the **current object** inside a member function.

```cpp
class Student {
public:
    string name;
    int age;

    Student(string name, int age) {
        this->name = name;    // this->name = data member,  name = parameter
        this->age = age;
    }
};
```

Uses:
1. Tell the data member apart from a parameter with the same name.
2. Return the current object: `return *this;` (used for chaining calls).

---

## 7. Static Members

A **static** member belongs to the **class**, not to any single object. All objects share it.

```cpp
class Student {
public:
    static int count;        // shared by all objects

    Student() { count++; }

    static void showCount() {    // can only use static members
        cout << count << endl;
    }
};

int Student::count = 0;      // must be defined outside the class

int main() {
    Student a, b, c;
    Student::showCount();    // 3
    return 0;
}
```

- A static function has **no `this` pointer**, so it cannot use non-static members.
- Call it with the class name: `Student::showCount()`.

---

## 8. Shallow Copy vs Deep Copy

This matters when a class holds a **pointer** to heap memory.

- **Shallow copy:** copies the pointer value, so both objects point to the **same** memory.
- **Deep copy:** allocates **new** memory and copies the data.

```
Shallow:   a.data ----\
                       >---> [10, 20, 30]      (one shared block)
           b.data ----/
           When a and b are destroyed, the block is deleted twice -> crash

Deep:      a.data ---> [10, 20, 30]
           b.data ---> [10, 20, 30]            (separate blocks)
```

```cpp
class Array {
public:
    int *data;
    int n;

    Array(int n) {
        this->n = n;
        data = new int[n];
    }

    // Deep copy constructor
    Array(const Array &other) {
        n = other.n;
        data = new int[n];                  // new memory
        for (int i = 0; i < n; i++) {
            data[i] = other.data[i];        // copy the values
        }
    }

    ~Array() {
        delete[] data;
    }
};
```

> The default copy constructor does a **shallow** copy. If your class uses `new`, write your own copy constructor and destructor.

---

## 9. The 4 Pillars of OOP

| Pillar | One-line meaning | C++ tool |
|--------|------------------|----------|
| **Encapsulation** | Bundle data + functions, and hide the data | `private` + getters/setters |
| **Abstraction** | Show only what is needed, hide the details | abstract classes, functions |
| **Inheritance** | A new class reuses an existing class | `class B : public A` |
| **Polymorphism** | One name, many behaviours | overloading, `virtual` |

---

## 10. Encapsulation

Keep data **private** and give controlled access through public functions.

```cpp
class BankAccount {
private:
    double balance;

public:
    BankAccount() { balance = 0; }

    void deposit(double amt) {
        if (amt > 0) balance += amt;      // validation protects the data
    }

    bool withdraw(double amt) {
        if (amt > 0 && amt <= balance) {
            balance -= amt;
            return true;
        }
        return false;
    }

    double getBalance() { return balance; }    // getter
};

int main() {
    BankAccount acc;
    acc.deposit(500);
    acc.withdraw(200);
    cout << acc.getBalance();    // 300
    // acc.balance = 1000000;    // ERROR: balance is private
    return 0;
}
```

**Why:** nobody can set `balance` to a wrong value, because every change goes through code you control.

---

## 11. Abstraction

Hide the **how**, show only the **what**. When you press a car's accelerator, you don't need to know how the engine works.

In C++, abstraction is done with:
- **Access specifiers** (hide the internal details)
- **Abstract classes** (a class with at least one pure virtual function, see section 13)

| Encapsulation | Abstraction |
|---------------|-------------|
| Hides **data** | Hides **implementation** |
| Solved at the implementation level | Solved at the design level |
| Done with `private` | Done with abstract classes / interfaces |

---

## 12. Inheritance

A **derived (child)** class gets the properties and functions of a **base (parent)** class. This gives code reuse and an "is-a" relationship (a Dog **is an** Animal).

```cpp
class Animal {
public:
    string name;
    void eat() { cout << name << " is eating" << endl; }
};

class Dog : public Animal {
public:
    void bark() { cout << name << " is barking" << endl; }
};

int main() {
    Dog d;
    d.name = "Tommy";
    d.eat();     // inherited from Animal
    d.bark();    // Dog's own function
    return 0;
}
```

### Types of inheritance

| Type | Shape | Example |
|------|-------|---------|
| Single | A -> B | Animal -> Dog |
| Multilevel | A -> B -> C | Animal -> Dog -> Puppy |
| Multiple | A, B -> C | Class C inherits from both A and B |
| Hierarchical | A -> B, A -> C | Animal -> Dog, Animal -> Cat |
| Hybrid | mix of the above | Multiple + hierarchical |

### Inheritance modes

How the base class members look **inside the derived class**:

| Base member | `public` inheritance | `protected` inheritance | `private` inheritance |
|-------------|:-------------------:|:-----------------------:|:---------------------:|
| `public` | public | protected | private |
| `protected` | protected | protected | private |
| `private` | not accessible | not accessible | not accessible |

> A base class's `private` members are **never** directly accessible in the derived class in any mode. Use `protected` if the child needs access.

### Constructor and destructor order

```cpp
class A { public: A() { cout << "A "; }  ~A() { cout << "~A "; } };
class B : public A { public: B() { cout << "B "; }  ~B() { cout << "~B "; } };

int main() {
    B obj;
    return 0;
}
// Output: A B ~B ~A
```

- Constructors: **base first**, then derived.
- Destructors: **derived first**, then base (reverse order).

### Diamond problem
If `B` and `C` both inherit from `A`, and `D` inherits from both `B` and `C`, then `D` gets **two copies** of `A`. Fix it with **virtual inheritance**:

```cpp
class B : virtual public A {};
class C : virtual public A {};
class D : public B, public C {};   // only one copy of A now
```

---

## 13. Polymorphism

*Poly = many, morph = forms.* The same function name behaves differently in different situations.

| | Compile-time (static) | Run-time (dynamic) |
|--|----------------------|--------------------|
| Decided | by the compiler | while the program runs |
| Achieved by | function overloading, operator overloading | function overriding with `virtual` |
| Speed | faster | slightly slower (vtable lookup) |

### a) Function overloading (compile-time)
Same name, **different parameters**.

```cpp
class Print {
public:
    void show(int x)         { cout << "int: "    << x << endl; }
    void show(double x)      { cout << "double: " << x << endl; }
    void show(string x)      { cout << "string: " << x << endl; }
};

int main() {
    Print p;
    p.show(5);          // int: 5
    p.show(2.5);        // double: 2.5
    p.show("hello");    // string: hello
    return 0;
}
```
Changing only the return type is **not** valid overloading.

### b) Operator overloading (compile-time)
Give operators a meaning for your own class.

```cpp
class Complex {
public:
    int re, im;
    Complex(int r, int i) : re(r), im(i) {}

    Complex operator+(const Complex &o) {
        return Complex(re + o.re, im + o.im);
    }
};

int main() {
    Complex a(2, 3), b(4, 5);
    Complex c = a + b;
    cout << c.re << " + " << c.im << "i";    // 6 + 8i
    return 0;
}
```

### c) Function overriding (run-time)
A derived class gives its **own version** of a base class function. Mark the base function `virtual` so the call is decided by the **actual object type**, not the pointer type.

```cpp
class Animal {
public:
    virtual void sound() { cout << "Some sound" << endl; }
    virtual ~Animal() {}                 // virtual destructor (see below)
};

class Dog : public Animal {
public:
    void sound() override { cout << "Bark" << endl; }
};

class Cat : public Animal {
public:
    void sound() override { cout << "Meow" << endl; }
};

int main() {
    Animal *a1 = new Dog();
    Animal *a2 = new Cat();
    a1->sound();      // Bark   (without virtual it would print "Some sound")
    a2->sound();      // Meow
    delete a1;
    delete a2;
    return 0;
}
```

- `override` makes the compiler check that you really are overriding a base function.
- If you delete a derived object through a base pointer, the base destructor must be **virtual**. Otherwise only the base destructor runs, and the derived part leaks.

### d) Abstract class & pure virtual function
A class with at least one **pure virtual function** (`= 0`) is **abstract**. You cannot create objects of it. Derived classes **must** implement the function.

```cpp
class Shape {
public:
    virtual double area() = 0;           // pure virtual
    virtual ~Shape() {}
};

class Circle : public Shape {
    double r;
public:
    Circle(double r) : r(r) {}
    double area() override { return 3.14 * r * r; }
};

class Rectangle : public Shape {
    double l, b;
public:
    Rectangle(double l, double b) : l(l), b(b) {}
    double area() override { return l * b; }
};

int main() {
    // Shape s;                          // ERROR: abstract class
    Shape *s1 = new Circle(2);
    Shape *s2 = new Rectangle(3, 4);
    cout << s1->area() << endl;          // 12.56
    cout << s2->area() << endl;          // 12
    delete s1;
    delete s2;
    return 0;
}
```

---

## 14. Common Mistakes

| Mistake | Problem | Fix |
|---------|---------|-----|
| Forgetting `;` after a class | Compile error | `class A { ... };` |
| Accessing a `private` member outside | Compile error | Use a public getter/setter |
| Giving the constructor a return type | It becomes a normal function | No return type at all |
| Copy constructor taking a value | Infinite recursion | Take `const Class &` |
| Class with `new` but no copy constructor | Shallow copy, double delete | Write a deep copy constructor |
| Overriding without `virtual` | Base version is called through a base pointer | Mark the base function `virtual` |
| Non-virtual destructor in a base class | Derived part is not destroyed, memory leak | `virtual ~Base() {}` |
| Using `this` in a static function | No `this` exists there | Use only static members |
| Defining a static data member only inside the class | Linker error | `int Class::count = 0;` outside |

---

## 15. Quick Cheat Sheet

| Concept | Remember |
|---------|----------|
| Class vs object | blueprint vs instance |
| Default access | `class` -> private, `struct` -> public |
| Constructor | same name as class, no return type, auto-called |
| Destructor | `~Class()`, one only, runs at destruction |
| Copy constructor | `Class(const Class &o)` |
| `this` | pointer to the current object |
| `static` | shared by all objects, defined outside the class |
| Deep copy | needed whenever the class owns heap memory |
| Encapsulation | private data + public functions |
| Abstraction | hide implementation, show behaviour |
| Inheritance | `class D : public B`, constructors run base first |
| Overloading | same name, different parameters (compile-time) |
| Overriding | `virtual` + `override` (run-time) |
| Abstract class | has `= 0` function, no objects possible |
| Virtual destructor | always add one to a base class |

### Practice Problems
- Create a `Student` class with a constructor, a destructor and a display function
- Build a `BankAccount` class with deposit, withdraw and balance check
- Create a `Shape` hierarchy (Circle, Rectangle, Triangle) with a virtual `area()`
- Overload `+` and `==` for a `Complex` or `Fraction` class
- Implement a `Stack` class (it will help with the next DSA topic)
- Show the order of constructors and destructors in multilevel inheritance
