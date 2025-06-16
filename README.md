# 🐚 Minishell

A small shell written in C, following the POSIX standard, developed as a project at 42 School.  
But don’t be fooled by “mini” – behind the scenes there's a full parser, signal handling, pipes, redirections, and lots of fun with `execve`. 😎

---

## 🚀 Goal

Rebuild a basic shell that can execute commands like Bash, including:

- Commands with arguments (`ls -la`, `echo hello`)
- Redirections (`>`, `<`, `>>`, `<<`)
- Pipes (`|`)
- Variable expansion (`$HOME`, `$?`)
- Quote handling (`"`, `'`)
- Signal handling (`Ctrl+C`, `Ctrl+\`)
- Builtins: `cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`

---

## ⚙️ How to Compile

```bash
make

#This will produce the executable named minishell.

./minishell

minishell$ echo "Hello world"
Hello world

minishell$ ls | wc -l

minishell$ export VAR=42
minishell$ echo $VAR
42

minishell$ cat << EOF
> hello
> world
> EOF
hello
world

🧠 Project Structure

The project is modular and divided into logical components:
Module	Description
Tokenizer	Splits the user input into tokens, handling quotes and escapes
Lexer	Classifies tokens (word, operator, redirection, etc.)
Parser	Builds the command structure (t_cmd)
Executor	Handles pipes, redirections, and runs each command
Builtins	Implements internal commands like cd, export, exit, etc.
Expander	Expands variables ($VAR) to their corresponding values
Signals	Manages interruptions like Ctrl+C without killing the shell
Heredoc	Supports multiline input using << with pipe-based input

👨‍💻 Built-in Commands

    echo

    cd

    pwd

    export

    unset

    env

    exit

🧩 Cool Things We Learned

    How to use fork(), execve(), pipe(), dup2() and wait()

    Memory and process management

    Complex parsing with quotes and redirections

    Variable expansion like Bash

    Heredoc implementation without temp files – pure pipe magic!

⚠️ What’s Not Included (Yet)

    &&, ||, and ; (bonus)

    Command history

    Wildcards (*)

    Full Bash compatibility

🧹 Cleaning

make fclean

