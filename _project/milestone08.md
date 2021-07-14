---
layout: default
title:  "Milestone 08 (optional)"
parent: Project
categories: project
author : Lars Pastewka
nav_order: 9
---

# Milestone 8 (optional) <br/> Parallelization

## Learning goals

The student will...
* ...learn how to work with the message passing interface (MPI).
* ...be able to use domain decomposition as a parallelization strategy.
* ...learn how to run parallel simulations on supercomputers.

## Introduction

The system sizes that are accessible with our code are limited by the computational power of a single CPU. Parallelization allows us to use multiple CPUs for the computing task at hand. In this milestone, we will parallelize the code using a strategy called *domain decomposition*. The physical domain of our simulation is decomposed in to subdomains that each "live" on a single CPU. More specifically, we will use a Cartesian decomposition of the overall domain. Since both potential encounterd so far (Lennard-Jones and EAM) are short-ranged, meaning the interaction only extends to a certain distance, the necessary subdomain need to "talk" only to their respective neighbors. This leads to a communication pattern that effectively scales extremely well, easily beyond $$100\,000$$ CPUs.

## MPI prerequisites

Starting with this milestone, we will make use of the [Message Passing Interface (MPI)](https://en.wikipedia.org/wiki/Message_Passing_Interface). For this, we need to setup the build system and we need to initialize our application correctly.

### Build system

The skeleton repository that we provided for you already contained the configuration for MPI. The toplevel `CMakeLists.txt` contains a statement `find_package(MPI REQUIRED)` that enables MPI for your project. This means all your code is compiled with the MPI compiler wrapper `mpicc`, `mpicxx` or `mpic++` that takes care of linking you program to the correct MPI libraries. You can still run your program (`milestone08`) in a normal fashion (as you have done in the past milestones); this is equivalent to running on a single process via `mpirun -n 1 ./milestone08`. 