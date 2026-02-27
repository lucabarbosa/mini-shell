# Minishell
> *This project was created as part of the 42-SP curriculum by Luca (lbento) and Ian (iaratang).*

This project is a simplified version of Unix shell written in C, developed as part of the 42 School curriculum. **minishell** reproduces the core behavior of `bash`, including tokenization, command execution, pipelines, redirections, environment variable expansion, and built-in commands — all built from scratch using low-level system calls.

The Minishell requires students to implement core shell functionalities such as:

- Displaying a dynamic command prompt
- Parsing and executing user input
- Handling environment variables
- Managing processes using fork, execve, and wait
- Implementing input and output redirections `>`, `>>`, `<`
- Supporting pipes `|`
- Handling signals like `ctrl+C`, `ctrl+D`, and `ctrl+\`
- Recreating essential built-in commands such as `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`

This project is a deep dive into how a real shell works under the hood.

---

## Table of Contents

- [Instructions](#instructions)
  - [Requirements](#requirements)
  - [Installation](#installation)
  - [Compiling](#compiling)
  - [Running](#running)
- [Usage Examples](#usage-examples)
- [Bibliography](#bibliography)

---

## Instructions

### Requirements

Before compiling and running **minishell**, make sure your Linux machine has the following installed:

| Dependency | Purpose |
|---|---|
| `gcc` (≥ 9) or `cc` | C compiler (C99 standard) |
| `make` | Build automation |
| `readline` library | Line editing and input history |
| `libreadline-dev` | Development headers for readline |

**Note:** The `readline` library is **mandatory**. Without it, the project will not compile.

### Installation

On a Debian/Ubuntu-based Linux system, install all required dependencies with:

```bash
sudo apt update
sudo apt install -y gcc make libreadline-dev
```
Verify that everything is installed correctly:

```bash
gcc --version
make --version
pkg-config --libs readline   #should output something like: -lreadline
```

On MacOS:

```bash
brew install readline make
```

Verify the setup before is correctly:

```bash
brew --prefix readline        #should print the readline install path
ls $(brew --prefix readline)/include/readline/readline.h   #header must exist
```
> Note: The command brew --prefix readline command solver the correct path automatically regardless of whether the machine is Apple Silicon (M1/M2/M3) or Intel.

---

### Compiling

Clone the repository and compile the project:

```bash
git clone https://github.com/lbento/minishell.git
cd minishell
make     #If you using macOs use: make mac
```

This will generate the `minishell` executable in the project root directory.

To remove object files:

```bash
make clean
```

To remove object files and the executable:

```bash
make fclean
```

To recompile from scratch:

```bash
make re
```

To recompile and execute the minishell with valgrind:

```bash
make val
```
---

### Running

Launch the shell by executing:

```bash
./minishell
```

It will open with a custom prompt. From there, you can type commands like a regular Bash shell.

To exit the shell, type:

```bash
exit
```

Or press `Ctrl+D` (sends EOF).


## Usage Examples

Below are some commands you can test inside **minishell** to explore its features:

**Basic command execution:**
```bash
ls -la
echo "Hello, 42!"
pwd
```

**Environment variables:**
```bash
echo $HOME
export MY_VAR=hello
echo $MY_VAR
unset MY_VAR
echo $MY_VAR
```

**Built-in commands:**
```bash
cd /tmp
cd -
cd ~
pwd
env
exit 42
```

**Input and output redirections:**
```bash
echo "writing to file" > output.txt
cat < output.txt
echo "appending line" >> output.txt
cat output.txt
ls > f1 > f2 > -la
```

**Pipelines:**
```bash
ls | grep .c
cat Makefile | grep minishell
echo "hello world" | wc -w
cat << a | cat << b | cat << c 
```

**Combined pipeline with redirections:**
```bash
ls -la | grep .c > c_files.txt
cat c_files.txt
```

**Here-document (heredoc):**
```bash
cat << eof
line one
line two
eof
```

**Exit status:**
```bash
ls /nonexistent
echo $?
ls /tmp
echo $?
#press ctrl + C
echo $?
```

**Signals:**
- `Ctrl+C` — interrupts the current command or process
- `Ctrl+\` — does nothing
- `Ctrl+D` — exits the shell and process that receive EOF
```bash
cat
#press ctrl + C
cat
#press ctrl + \
cat
#press ctrl + D
sleep 90
#press ctrl + C
sleep 90
#press ctrl + \
sleep 90
#press ctrl + D
```

**Quoting:**
```bash
echo "This is $USER inside double quotes"
echo 'This is $HOME inside single quotes'
echo "Multiple     spaces    preserved"
```

## Bibliography

The following resources were used during the development of this project and are recommended for anyone who wants to understand the concepts involved:

### Official Manuals and Documentation

- **Bash Reference Manual** — The official GNU Bash documentation, covering everything from syntax to built-ins and job control.
  https://www.gnu.org/software/bash/manual/bash.html

- **POSIX Shell Command Language** — The formal POSIX specification for shell behavior, useful for understanding what is standard versus bash-specific.
  https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html

- **Linux `man` pages online** — Quick reference for all system calls and library functions used in minishell (`fork`, `execve`, `pipe`, `dup2`, `waitpid`, `readline`, etc.).
  https://man7.org/linux/man-pages/

### Books

- **"The Linux Programming Interface"** — Michael Kerrisk. The most comprehensive reference on Linux system programming, covering processes, file descriptors, signals, and more.
  https://man7.org/tlpi/

- **"Advanced Programming in the UNIX Environment"** — W. Richard Stevens & Stephen Rago. A classic reference for UNIX systems programming in C.

### Additional Resources

- **GNU Readline Library** — Official documentation for the readline library used for input handling and history.
  https://tiswww.case.edu/php/chet/readline/rltop.html

---

> *Don’t despair, dear cadet — this project is truly challenging. Trust the process!*