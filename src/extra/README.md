# Portability notes:

This library is developed with portability in mind, so this library in general can be used on:
- every standard operation system (like Linux, Windows or MacOS)
- non standard operation system (like various RTOS types)
- bare metal platforms.

This directory contains source files that provide functions that may require additional work to run 
the code (e.g. file operations). Don't worry about this if you would like to use it on standard 
operation system because every function inside this directory is already ported