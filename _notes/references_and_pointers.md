---
layout: default
title:  "C++ References and Pointers"
parent: Notes
categories: notes
author : Lucas Frérot
nav_order: 1
---

# C++ References and Pointers

References and pointers can cause confusion for beginners: this note aims to
clarify what references and pointers are good at, what are their differences and
how they can be used in C++.

## Passing function arguments

Programming language often distinguish themselves in how function arguments are
passed to functions. In C++, function arguments can typically be passed in three
ways:

- Pass-by-value
- Pass-by-reference
- Pass-by-address

Function arguments that are passed by value are essentially copied when passed
to the function that is called. In a language like Python for example, scalar
variables are passed by value. Function arguments that are passed by reference
are not copied: the variable available in the function *refers* to the variable
that was passed to the function.

Let us look at a C++ function that takes its arguments *by-value*.

```cpp
#include <iostream>

void increment(int x) {
    x += 1;
    std::cout << "value of x in function: " << x << "\n";
}

int main() {
    int y = 2;
    increment(y);
    std::cout << "value of x outside function: " << x << "\n";
    return 0;
}
```

The output of this program is:

```
value of x in function: 3
value of x outside function: 2
```

This means that the value of `y` was copied into the function argument `x`. Now
here is the same code, but the argument of `increment()` passed by reference.

```cpp
#include <iostream>

void increment(int& x) {
    x += 1;
    std::cout << "value of x in function: " << x << "\n";
}

int main() {
    int y = 2;
    increment(y);
    std::cout << "value of x outside function: " << x << "\n";
    return 0;
}
```

The output of this program is:

```
value of x in function: 3
value of x outside function: 3
```

The variable `x` inside the function `increment` *refers* to the variable `y`
outside the function. This has two common use cases:

- Modification of the variable within the function: functions can return values,
  but in imperative languages it is common to want to modify function arguments
  in addition to returning a value. This is known as a *side-effect* (i.e. when
  function arguments are modified). A relevant example would be to update
  particle velocities.
- Avoiding copies of large objects: scalar variables and short strings should be
  passed by value (this can save some bugs, and compilers can sometimes avoid
  the copy overhead), but large objects, such as arrays describing atoms
  positions, velocities, etc., should not be copied when they are passed on to
  functions. Passing by reference avoids this.
  
When one is in the second use case (copy needs to be avoided) but not in the
first case (arguments do not need, or should not, be modified), one can use a
*constant reference* argument.

```cpp
#include <iostream>
#include <vector>

auto size(const std::vector<int>& x) {
    return x.size();
}

int main() {
    std::vector<int> v = {1, 2, 3, 4};
    std::cout << "size of vector: " << size(v) << "\n";
    return 0;
}
```
