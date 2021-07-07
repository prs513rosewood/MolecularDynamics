---
layout: default
title:  "Milestone 05"
parent: Project
categories: project
author : Lars Pastewka
nav_order: 6
---

# Milestone 5 <br/> Berendsen thermostat

## Learning goals

The student will...
* ...learn how to implement a simple thermostat for temperature control.
* ...learn how to setup and equilibrate a fresh molecular system.

## Introduction

Thermostats are means of coupling a molecular system to a larger heat bath that controls the
temperature in the molecular system by exchanging energy with it. We will here implement the _Berendsen thermostat_
as a simple form of temperature control. A thermostat is essential to equilibrate a system during
the initial stage of a molecular dynamics run, that typically starts from a guess for the atomic
configuration that is far away from equilibrium. The thermostat then prevents a temperature rise above melting or
boiling points of the respective material that would destroy the initial configuration.

## Berendsen thermostat

The Berendsen thermostat is most straightforwardly implemented by rescaling the velocities by a factor

$$\lambda = \sqrt{1+ \left( \frac{T_0}{T} - 1 \right) \frac{\Delta t}{\tau}}$$

after each time step. This means after the second verlet step, rescale each velocity vector \\(\vec{v}_i\\) to the new value \\(\lambda \vec{v}_i\\). Here \\(T\\) is the current temperature measured from the current velocities \\(\vec{v}_i\\) and \\(T_0\\) is a user-specified target temperature. The relaxation time constant \\(\tau\\) is chosen by the user and \\(\Delta t\\) is the time step of the integration algorithm. The lecture material contains the full derivation of this expression and rationales for choosing the relaxation time constant.

### Implementation and tests

We suggest the following signature for the function that implements the rescaling step:
```c++
void berendsen_thermostat(Atoms &atoms, double temperature, double timestep,
                          double relaxation_time);
```
This function should directly modify the velocities in `atoms.velocities`.

This function should also be tested in your testing framework. Devise ways to test this function and implement those tests.

## Equilibrating a fresh molecular system

In Milestone 4, we provided an equilibrated Lennard-Jones system for you that you then propagated with your code. With the help
of the Berendsen thermostat, you are now in a position to start your own molecular calculations. Modify your code such that is can
be started with a flexible number of atoms. You will use this to test scaling (computational complexity) of your current
Lennard-Jones implementation.

A resonable starting point is to put the initial atoms on a lattice, the simplest lattice is a cubic one. Note that the lattice constant, the distance between the initial atomic positions determines how far you are from equilibrium and how difficult it will
be to equilibrate your system. Play with the lattice constant, a good starting point is \\(1\sigma\\).

When you run your calculation without a thermostat, you should see an increase in temperature (kinetic energy) and a decrease in potential energy. Add you Berendsen thermostat and play with the relaxation time constant. Pick one that is slow enough to allow the system to relax but fast enough to avoid evaporation. You should monitor the trajectory of your system to see if there are atoms
that evaporate from your cluster of Lennard-Jones atoms.

Note that the final relaxation time constant should be choses according to the rules laid out in the lecture. This may mean that you need to set up a series of runs in which you start with a short time constant and then continue running with a larger one as
your atomic system has moved closer to equilibrium. Monitor kinetic and potential energies during this process and try to understand what is happening.

## Computational complexity

Equilibrate systems with different particle numbers and measure the time it takes to run the simulation for a fixed number of time steps. You can measure the time with the [`time`](https://www.gnu.org/software/time/) command. For example, my simulation code is called YAMD (=Yet Another Molecular Dynamics Code), I would simply run
```bash
time ./yamd
```
to measure the execution time of my code. Plot the execution time versus the number of particles. What do you see?

## Task summary

This milestone requires the following tasks:

* Implement the Berendsen thermostat
* Devise tests for the Berendsen thermostat and implement those
* Implement creation of atomic lattices
* Devise an equilibration strategy and equilibrate a number of Lennard-Jones clusters with different numbers of atoms
* Measure the simulation time as a function of the number of atoms in your system

We ask you to provide the following analytical results in your final report:

* Explain your test strategy for the Berendsen thermostat

We ask you to provide and discuss the following figures in your final report:

* Plot of the simulation time as a function of the size (number of atoms) of your atomic system
