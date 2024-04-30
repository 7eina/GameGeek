# GameGeek

## Project Overview

This project is for the GameGeek platform, which tracks gaming sessions for users. It involves creating several classes in C++ to manage games and sessions, focusing on the backend logic without a user interface. Instead, a test suite will be used for validation.

Created: Summer 2023

## Files Included

- **Date.h/cpp**: Manages date operations. Includes comparison functions to sort dates.
- **Session.h/cpp**: Stores details about a single gaming session, including the date, duration, and achievement.
- **Game.h/cpp**: Contains and manages sessions for a single game, handling operations like adding and sorting sessions.
- **GameGeek.h/cpp**: The main class that orchestrates operations between games and sessions.
- **main.cc**: Contains the main function and testing logic provided in the starter code.
- **defs.h**: Includes definitions and constants used throughout the application.
- **Makefile**: Script for compiling the project into an executable.

## Directory Structure

- **src/**: Contains all `.cpp` files.
- **include/**: Contains all `.h` header files.
- **tests/**: (Optional) Contains additional test files for personal testing.

## Compilation Instructions

To compile the project, use one of the following commands:

```bash
make all
```
