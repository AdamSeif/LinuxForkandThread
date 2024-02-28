# Readme

This repository contains a collection of C programs that demonstrate inter-process communication using processes and pipes in a Unix-like environment.

## Programs

1. **`main.c`**: This program orchestrates the execution of other programs by forking processes and executing external programs.
   
2. **`external_program1.c`**: This program calculates the sum of numbers from 1 to a given number `R`.

3. **`external_program2.c`**: This program simply prints a greeting message.

4. **`child_1.c`**: This program calculates partial sums of a sequence of numbers.

## Instructions

1. **Compilation**: To compile these programs, use a C compiler such as `gcc`. For example:
   

2. **Execution**: After compilation, execute the `main` program along with three arguments: `N`, `M`, and `S`.

- `N`: An integer specifying the range for calculating the sum.
- `M`: An integer specifying the number of processes to spawn for parallel computation.
- `S`: A string argument.

Example:

./main 100 4 "Hello World"

## Note

- Ensure that the external programs (`external_program1.c` and `external_program2.c`) are compiled and located at the specified paths before executing the `main` program.

- This setup assumes a Unix-like environment with standard C libraries and system calls.

- Carefully manage the arguments passed to the programs to ensure proper execution.

- These programs are provided as educational resources and may require modifications for specific use cases.
