# 📟 Minishell

> This project is a bash-based mini shell written in C

## 📖 Description

**Minishell** is a 42 school project where the goal is to recreate a simple shell (command-line interpreter) in C, heavily inspired by `bash`.

### Project Goal
The main objective is to understand how a shell works under the hood, from parsing the command line to executing it, while diving deep into process management, file descriptors, redirections, and signals. It offers a fascinating plunge into the inner workings of the Unix operating system.

### Features
* **Interactive Prompt**: Displays a prompt and waits for user input (via `readline`).
* **History**: Keeps a history of previously entered commands.
* **Command Execution**: Finds and executes binaries (using the `PATH` environment variable or relative/absolute paths).
* **Pipes (`|`)**: Connects the standard output of a command to the standard input of the next.
* **Redirections**: 
  * `<`: Redirects input.
  * `>`: Redirects output (overwrites the file).
  * `>>`: Redirects output (appends to the file).
  * `<<` (Here-document): Reads input until a delimiter is encountered.
* **Environment Variables**: Handles variable expansion (e.g., `$USER` or `$?`).
* **Builtins**:
  * `echo` (with the `-n` option)
  * `cd` (with only a relative or absolute path)
  * `pwd` (prints the current working directory)
  * `export` (sets environment variables)
  * `unset` (unsets environment variables)
  * `env` (prints the environment)
  * `exit` (exits the shell)
* **Signal Handling**: Reacts properly to `ctrl-C`, `ctrl-D`, and `ctrl-\` just like `bash`.

---

## 🚀 Instructions

### Prerequisites
The project is written in **C**. To run it, you will need:
* A C compiler (`gcc` or `clang`)
* The `make` utility
* The `readline` library installed on your system.

### Compilation
A `Makefile` is provided at the root of the project. To compile the project, open a terminal, navigate to the project directory, and run:

```bash
make
```

This will generate the `minishell` executable.

Other available rules are:
* `make clean`: Removes the object files (`.o`).
* `make fclean`: Removes the object files and the executable.
* `make re`: Recompiles the entire project.

### Execution
Once compiled, you can launch the shell by running:

```bash
./minishell
```

When the prompt appears, you can use `minishell` just like any other shell.

**Usage Example:**
```bash
minishell$ echo "Hello World!" | cat -e > output.txt
minishell$ cat output.txt
Hello World!$
minishell$ exit
```
