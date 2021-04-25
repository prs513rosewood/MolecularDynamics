---
layout: default
title:  "Milestone 2"
parent: Project
categories: project
author : Lars Pastewka
nav_order: 2
---

## Milestone 2 <br/> Velocity-Verlet integration

## Introduction

In this second milestone you will implement a Velocity-Verlet integrator. You will learn about header and source
files and how to add them to the CMake build system. You will also need to think about *testing*, i.e. how do
you systematically test an implementation. Testing makes sure your new function works correctly but it also makes
sure that you will notice when you break it in the future. Note that we explain only the very basics of the
relevant C++ features here but link to more detailed explanation.

### Adding a header/source file

We recommend to add the integration functionality into a new module that consists of a header and source file.
The header file typically has the extension `.h` and contains only the signatures (also called interfaces) of
the functions. It is required such that the module can be used from another source file.

Create a file `verlet.h` with the following contents:
```c++
#ifndef __VERLET_H
#define __VERLET_H

#include <Eigen/Dense>

void verlet_step1(Eigen::Array3Xd &positions, Eigen::Array3Xd &velocities, const Eigen::Array3Xd &forces,
                  double timestep);
void verlet_step2(Eigen::Array3Xd &velocities, const Eigen::Array3Xd &forces, double timestep);

#endif  // __VERLET_H
```
The `#ifndef __VERLET_H` commands are called a [header guard](https://en.wikipedia.org/wiki/Include_guard) and
avoid double inclusion of the file (e.g. in a chain of include statements). Everything that starts with a `#`
is processed by the [preprocessor](https://en.wikipedia.org/wiki/C_preprocessor) which produces the file that
is actually compiled by the C++ compiler.

We here suggest to use [Eigen arrays](https://eigen.tuxfamily.org/dox/group__TutorialArrayClass.html) as the basic
datatype. These arrays support component-wise operation, i.e. we can multiply the whole array by a number or add
the contents of two arrays without having to loop over them.

The `&` symbol in the function signature is a [reference](https://en.wikipedia.org/wiki/Reference_(C%2B%2B)). It tells the
compiler to pass only the memory location of the underlying data rather than copying it. It should be used for large
compound types. (Passing `int`egers or `double` floating point numbers without reference is fine.) Note that arguments
passed as a reference can be modified inside the function, which is why we can update positions and velocities inside
`verlet_step1`. The [`const` qualifier](https://en.cppreference.com/w/c/language/const) tells the compiler that a modification
is not allowed. (We don't need to modify the forces and it is good practice to protect the with this `const` qualifier
to avoid accidental modification.)

The corresponding source file `verlet.cpp` should look like this:
```c++
#include "verlet.h"

void verlet_step1(Eigen::Array3Xd &positions, Eigen::Array3Xd &velocities, const Eigen::Array3Xd &forces,
                  double timestep) {
    ... implement Verlet step1 here ...
}

void verlet_step2(Eigen::Array3Xd &velocities, const Eigen::Array3Xd &forces, double timestep) {
    ... implement Verlet step2 here ...
}
```
Header and source files have typically extensions `.h` and `.cpp`. On Unix system, you sometimes find `.hh` and `.cc`
for C++ code.

To compile the code, you need to add headers files to `MYPROJECT_HDRS` and sources files to `MYPROJECT_SRCS` in the
main `CMakeLists.txt`. From the command-line, you can compile the code by running `make` in the `build` directory.

### Testing the integrator

It is important to properly test _any_ implementation. You can even adopt a [test-driven development](https://en.wikipedia.org/wiki/Test-driven_development)
style in which tests are written before the implementation. We also here encourage you to write tests for all parts
of your molecular dynamics code. We will outline possible testing strategies in the respective milestones.

One possible test strategy for numerical code is to compare a numerical solution against a known analysical solution.
We are here solving Newton's equation of motion. Think which problem you can possibly solve analytically and then write
a test for it.

To add a new test, create a new file to the `tests` subdirectory and add it to the `myproject_tests_SRCS` in `CMakeLists.txt`
in the `tests` directory. You can copy the file `test_hello_world.cpp` as a template. The project uses [Googletest](https://google.github.io/googletest/).
Please browse the documentation and look at the primer on the documentation page.

A _test case_ consists of a number of _assertion_. An assertion defines a certain outcome of the function to be tested.
As an example, let us assume we were writing a test for a `sin` function. We know for example than the function vanishes
at integer multiples of $\pi$.
