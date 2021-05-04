---
layout: default
title:  "Milestone 4"
parent: Project
categories: project
author : Lars Pastewka
nav_order: 4
---

## Milestone 4 <br/> Lennard-Jones potential with direct summation

### Learning goals

The student will...
* ...learn how to implement a simple interatomic potential.
* ...learn how to systematically test the implementation of this interatomic potential.

### Introduction

We will now implement our first interatomic potential: A Lennard-Jones interaction. The
energy of a system interacting via Lennard-Jones forces is given by

$$E_\text{pot} = \frac{1}{2} \sum_{ij} 4 \varepsilon \left[ \left(\sigma/r_{ij}\right)^{12} - \left(\sigma/r_{ij}\right)^6\right]$$

The term \\(\propto r^{-12}\\) is a simple model for Pauli repulsion and the term \\(\propto r^{-6}\\) is a model for London dispersion forces.
Within this milestone, you will implement this potential via direct summation, i.e. directly using the equation given above.

### A data structure for the atomic system

Before starting, we introduce a data structure that holds the information on the atomic system, i.e. the positions, velocities, forces etc.
This makes it easier to pass the atomic system around. We suggest a data structure of the form:
```c++
using Positions_t = Eigen::Array3Xd; 
using Velocities_t = Eigen::Array3Xd; 
using Forces_t = Eigen::Array3Xd; 
 
class Atoms { 
public: 
    Positions_t positions; 
    Velocities_t velocities; 
    Forces_t forces; 
 
    Atoms(Positions_t &p) : 
            positions{p}, velocities{3, p.cols()}, forces{3, p.cols()} { 
        velocities.setZero(); 
        forces.setZero(); 
    } 
 
    size_t nb_atoms() const { 
        return positions.cols(); 
    }
};
```
The [`const` qualifier](https://en.cppreference.com/w/c/language/const) tells behind `nb_atoms` tells the compiler that this method does not change
the state of the `Atoms` object.
Place this data structure in a separate header file, e.g. `atoms.h`. We had already discussed in [Milestone 3] that the types should reside in their own
header, e.g. `types.h`. You can then simply include them in `atoms.h` by placing `#include "types.h"` somewhere at the beginning of the file.

### Function signature

Implement the Lennard-Jones potential. We suggest a function with the following signature:
```c++
double lj_direct_summation(Atoms &atoms, double epsilon = 1.0, double sigma = 1.0);
```
This signature defines default parameters for `epsilon` and `sigma`, i.e. they do need to be specified. Place this function in their own source and
header file, e.g. `lj_direction_summation.h` and `lj_direct_summation.cpp`.

### Testing the implementation

When implementing this function you will want to test that the forces that are computed are correct. In particular, the forces and energy need to be
consistent in the sense that the forces are the negative derivative of the energy. The energy is typically easy to implement correctly, but forces
can be fiddly. One sign of wrong forces is that energy in a molecular dynamics simulation is not conserved, but there are also other causes for
this effect (e.g. a time step that is too large) which makes it difficult as a test for the implementation of forces.

The common strategy is to compute the forces \emph{numerically} from the energies. For this, we have to compute a numerical first derivative.
This is straightforward to do from the difference quotient, e.g.

$$ f'(x) \approx \frac{f(x+\Delta x) - f(x-\Delta x)}{2 \Delta x}$$

A formal derivation of this expression can be obtained from a Taylor expansion of \\(f(x)\\). We can use this expression to compute numerical
estimates of the forces. A test that uses this to test the analytical forces of the potential can be found here: [test_lj_direct_summation.cpp](test_lj_direct_summation.cpp).
Place this file in your `tests` subdirectory and add it to the `CMakeLists.txt` to use it. Open it in an editor and try to understand how the test works.

