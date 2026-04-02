*This project has been created as part of the 42 curriculum by aborel, tniambi-.*

# Description

A minimalist Unix shell written in C, crafted as part of the **42 School** curriculum. `minishell` replicates core Bash behaviors — parsing, execution, redirections, pipes, signals, and builtins — from scratch.
`minishell` is a collaborative project at 42 School that challenges students to build a functional command-line interpreter in C. The goal is to deeply understand how shells work — from tokenizing user input to forking processes and handling signals — without relying on external libraries beyond `readline`.

# Instructions

After compiling, you can launch ./minishell in bash.

## Features

- **Interactive prompt** with command history (via `readline`)
- **Command execution** from `PATH`, relative, or absolute paths
- **Pipes** `|` — chain commands together
- **Redirections:**
  - `<` — input redirection
  - `>` — output redirection (truncate)
  - `>>` — output redirection (append)
  - `<<` — heredoc
- **Environment variable expansion** (`$VAR`, `$?`)
- **Single `'`** and **double `"` quotes** handling
- **Signal handling:** `Ctrl+C`, `Ctrl+D`, `Ctrl+\`
- **All required builtins**

## Builtins

The following builtins are implemented :

| Builtin | Description |
|--------|-------------|
| `echo` | Print arguments to stdout |
| `cd` | Change the current directory |
| `pwd` | Print the current working directory |
| `export` | Set environment variables |
| `unset` | Unset environment variables |
| `env` | Display the current environment |
| `exit` | Exit the shell with an optional status code |

# Resources

- [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
- [GNU Readline](https://tiswww.case.edu/php/chet/readline/rltop.html)

---
