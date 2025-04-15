# SquareMat - Square Matrix Operations Library

## Project Overview

This project implements a square matrix class in C++ that supports various matrix operations. It demonstrates object-oriented programming concepts, operator overloading, and memory management.

## Directory Structure

```
CPP_EX2_25/
├── inc/                 # Header files
│   ├── SquareMat.hpp    # Matrix class declaration
│   └── doctest.h        # Testing framework
├── src/                 # Implementation files
│   ├── SquareMat.cpp    # Matrix class implementation
│   ├── main.cpp         # Demo program
│   └── matxTest.cpp     # Test suite
├── obj/                 # Compiled object files
└── makefile             # Build configuration
```

## Features

The `SquareMat` class supports:

- Matrix creation in various ways (empty, from array)
- Basic operations (+, -, *)
- Scalar operations (*, /, %)
- Special operations (determinant, transpose)
- Comparison operations (==, !=, <, >, <=, >=)
- Increment/decrement operations (++, --)
- Compound assignment operations (+=, -=, *=, etc.)

## How to Build and Run

The project includes a makefile with several targets:

- `make all`: Builds both the main program and tests
- `make Main`: Builds and runs the main program
- `make test`: Builds and runs the test suite
- `make valgrind`: Checks for memory leaks
- `make clean`: Cleans up build files

## Class Design

Implemented the `SquareMat` class with a dynamic 2D array to store matrix elements. To safely access matrix elements with bounds checking, I created a inner class for the `[][]` operation.

Matrix operations follow standard mathematical definitions. For example, matrix multiplication implements the standard row-by-column multiplication algorithm, and the determinant is calculated recursively.

## Testing

Used the doctest framework to create a comprehensive test suite that verifies:

- All operators work correctly
- Edge cases are handled properly
- Exceptions are thrown when expected (invalid dimensions, out-of-bounds access)

## Conclusion

This project demonstrates my understanding of C++ object-oriented programming, operator overloading, and memory management. The SquareMat class provides a useful foundation for applications requiring matrix operations.