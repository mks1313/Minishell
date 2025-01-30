# Minishell

![Minishell Project](https://img.shields.io/badge/Minishell-42-blue)

## Description

Minishell is a project aimed at implementing a small shell, a program that provides a command-line interface for interacting with the operating system. The main goal is to replicate some basic functionalities of a standard shell, such as command execution, input/output redirection, and signal handling.

This project is part of the 42 school curriculum and involves fundamental concepts in C programming and system-level programming.

## Features

- Execution of commands like `ls`, `cat`, `echo`, etc.
- Support for redirection operators (`>`, `<`, `>>`).
- Pipe (`|`) support for chaining commands.
- Environment variable management.
- Implementation of built-in commands like `cd`, `export`, `unset`, `exit`, etc.
- Signal handling for `Ctrl+C`, `Ctrl+D`, and `Ctrl+\`.
- Basic support for quotes (`"` and `'`).

## Requirements

- Unix-based operating system (Linux or macOS).
- GCC or any other compatible C compiler.
- [GNU Readline](https://tiswww.case.edu/php/chet/readline/rltop.html) (optional, but recommended for advanced line editing).

## Installation

1. Clone the project repository:
    ```bash
    git clone https://github.com/yourusername/minishell.git
    ```

2. Navigate to the project directory:
    ```bash
    cd minishell
    ```

3. Compile the project:
    ```bash
    make
    ```

## Usage

After compiling, you can run the minishell with the following command:

```bash
./minishell
