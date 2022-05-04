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
    std::cout << "value of y outside function: " << y << "\n";
    return 0;
}
```

The output of this program is:

```
value of x in function: 3
value of y outside function: 2
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
    std::cout << "value of y outside function: " << y << "\n";
    return 0;
}
```

The output of this program is:

```
value of x in function: 3
value of y outside function: 3
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

### Pass-by-address

In C++, pointers are variables whose value is an address in memory. That address
*should* be the address of another existing variable, or the `nullptr` value,
which is an invalid address. Passing a variable to a function *by-address* means
that the address of that variable is copied into a pointer in the function.

Passing a variable by-address is conceptually the same as passing by-reference
(with a few edge case exceptions). However, in C++ practice, pointers are not
used the same as reference. Since pointers are variables that contain an
address, an extra step is needed to access the value of the addressed variable.
This step is called **dereferencing**. Syntactically, this is done with the `*`
operator: if `x` is a pointer (i.e. a variable containing an address), then `*x`
is the *dereferenced* value, that is the value contained at the memory address
`x`. Here is a code sample that does the exact same thing as the `increment`
function above with a reference argument:

```cpp
#include <iostream>

void increment(int* x) {
    *x += 1;
    std::cout << "value of x in function: " << x << "\n";
    std::cout << "value of *x in function: " << *x << "\n";
}

int main() {
    int y = 2;
    increment(&y);
    std::cout << "value of y outside function: " << y << "\n";
    return 0;
}
```

Here is a sample output:

```
value of x in function: 0x7ffcc6017a84
value of *x in function: 3
value of y outside function: 3
```

Notice two things that changed with regard to the by-reference code above:

- In `main()`, the `increment()` function is called not with `y`, but with `&y`.
  The ampersand `&` prefix to the variable indicates that we *pass the address*
  of the variable `y`, not its value. Try to pass `y` instead of `&y` and the
  compiler will complain with a conversion error, because `int` and `int*` are
  different variable types and one cannot convert into the other.
- To access the actual value we are interested in , we need to do `*x`. The
  value of `x` is an address, as can be seen in the output.
  

#### The special case of member variables

One can access member variables of an object in C++ with the `.` operator, e.g.
`atoms.positions` is the variable `positions` inside the object `atoms`. This
assumes that the object `atoms` is of type `Atoms` or `Atoms&`, i.e. it is the
original object or a reference to that object. If `atoms` is of type `Atoms*`,
we need to dereference it *before* accessing the member variable. One issue is
that the dereferencing operator `*` has priority lower than the `.` operator.
This means that `*atoms.positions` is understood by the compiler as
`*(atoms.positions)` which is not what we want. A way to fix this is to use
parentheses to specify the operator priority: `(*atoms).positions` is what we
want, because we dereference `atoms` before accessing the `positions` variable.
Since this parentheses syntax is heavy, and accessing members of pointer
variables is so common, C++ has an equivalent syntax: `atoms->positions`. This
does the dereferencing before the member access and is exactly equivalent to
`(*atoms).positions`. Within class functions, it is common to use the `this`
pointer to refer to member variables with the syntax `this->positions`. The
`this` pointer points to the current object, and is the C++ equivalent of the
`self` object in Python.
