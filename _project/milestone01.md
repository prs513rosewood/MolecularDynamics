---
layout: default
title:  "Milestone 1"
parent: Project
categories: project
author : Lars Pastewka
nav_order: 1
---

## Milestone 1 <br/> Setting up the build environment

### Introduction

In this first milestone we will set up a build environemnt and make sure
that you can compile C++ code on your computer. This will be the starting
point for the developments in the following milestones.

### Setting up your system

The starting point of your project is setting up a proper build environment.
This means, you need to install and test all tools necessary for the project.
In particular, you will need:
* A C++ compiler
* [CMake](https://cmake.org) (at least version 3.11) for our build environment
* An [MPI](https://en.wikipedia.org/wiki/Message_Passing_Interface) installation

We provide installation instructions for [Ubuntu](https://ubuntu.com/)
installations. If you have a Windows machine, we recommend to use
the [Windows Subsystem for Linux (WSL)](https://en.wikipedia.org/wiki/Windows_Subsystem_for_Linux).
Documentation on how to install WSL on Windows 10 can be found
[here](https://docs.microsoft.com/en-us/windows/wsl/install-win10).

Once you have these things set up, open a command shell and type
```bash
sudo apt-get update
sudo apt-get install cmake gcc clang gdb build-essential git cmake-curses-gui valgrind
sudo apt-get install openmpi-bin libopenmpi-dev 
```

We recommend using a development environment for developing code. We
ourselves use [CLion](https://www.jetbrains.com/clion/). Free educational
licenses CLion can be obtained [here](https://www.jetbrains.com/community/education/).

### Creating an empty repository

The first thing you need to do is to set up your build environment. We have
done this for you and provide a template repository here:
[https://github.com/imtek-simulation/cmake-skeleton/](https://github.com/imtek-simulation/cmake-skeleton/).
We will now be walking you through the process of obtaining this skeleton repository
from the command line. You can also carry out the whole process within CLion.

On [Github](github.com), you can simply create a new repository from our template. Navigate to
the link above and click on "Use this template". You will be asked for a new name of
the repository: Let's call this yamd (Yet Another Molecular Dynamics code). Since my
username is "pastewka", the repository now resides under

     https://github.com/pastewka/yamd

You can now check this repository out, i.e. copy it to your local machine. On the shell,
type
```bash
git clone git@github.com:pastewka/yamd.git
```
(and replace "pastewka" and "yamd" with whatever is appropriate for you). The
code now resides in the subdirectory "yamd". Note that if you do not want to work
on github, you can also directly check out the template repository.

Our template repository has existing CMake files. Those CMake files are set up
to automatically download the libraries

* [Eigen](https://eigen.tuxfamily.org/) for basic (array) data structures and
* [Googletest](https://github.com/google/googletest) as a testing framework.

We will work with these libraries throughout this class.

_Note_: If you are unfamiliar with the unix shell, we recommend
[this tutorial](https://swcarpentry.github.io/shell-novice/). We also strongly
recommend that you use version control (git). If you are unfamiliar with git
and want to learn more, see
[this tutorial](https://swcarpentry.github.io/git-novice/).

### Compiling the code

The template repository contains a file `main.cpp` that prints the string
"Hello world!" to screen and a simple test `test_hello_world.cpp`. We need
to instruct CMake to create what is called a `Makefile` that contains
instructions how to build the code. CMake generally builds the code in a
directory that is separate from the source directory. This is different from
other build systems. We recommend that you create a directory `build` inside
your source directory.

First, navigate to the source code and create this directory:
```bash
cd yamd
mkdir build
cd build
```

Now, create the makefiles:
```bash
cmake ..
```
The argument to `cmake` tells it where the source code is located, here in
the directory level just upwards of the current one (i.e. in `..`). You can
also build in any other directory but then need to specify the appropriate
path when running `cmake`.

Note that `cmake` has lots of configuration options. To see those, run the
text-based user interface:
```bash
ccmake ..
```
The additional `c` in front stands for `curses`, the library that is used to
create the text-based user interface.

You can now execute
```bash
make
```
to compile the code. Now run
```bash
./myproject
tests/myproject_tests
```
If this worked, you have successfully compiled the hello world program and
its tests.
