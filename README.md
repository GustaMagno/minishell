*This project has been created as part of the 42 curriculum by gustoliv and matmagal.*

# minishell

## Description
`minishell` is a simplified Unix shell built in C as part of the 42 curriculum.
The main goal is to understand how a real shell works by implementing parsing,
expansion, process creation, pipes, redirections, built-ins, environment
management, exit status handling, and signal behavior.

This project reproduces core shell behavior for common commands while keeping a
clean and educational architecture split into parsing, execution, and utility
modules.

## Features
- Interactive prompt using GNU Readline.
- Command parsing with quote handling.
- Environment variable expansion (`$VAR`, `$?`).
- Built-ins: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.
- External command execution via `PATH`.
- Redirections: `<`, `>`, `>>`, `<<` (heredoc).
- Pipelines (`|`) with multiple commands.
- Signal handling for interactive shell behavior.

## Instructions
### Requirements
- Linux (or compatible Unix environment)
- `cc` compiler
- GNU Readline development library
- `make`

### Compilation
```bash
make
```
This builds the `minishell` executable at the repository root.

### Run
```bash
./minishell
```

### Useful Make targets
```bash
make clean      # remove object files
make fclean     # remove object files and binary
make re         # full rebuild
make r          # rebuild and run
make v          # run with valgrind (suppression file)
make vl         # valgrind full leak check
make vall		# valgrind  full leak check with FD tracking
```

## Project Structure
- `src/parse/`: lexical/syntax handling, expansion, command splitting.
- `src/exec/`: built-ins, process execution, pipes, redirections, heredoc.
- `src/map/`: environment map utilities.
- `src/utils/`: helper functions and generic utilities.
- `include/`: public headers.

## Resources
### Classic references
- GNU Bash Manual: https://www.gnu.org/software/bash/manual/
- POSIX Shell Command Language: https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html
- Linux man pages: https://man7.org/linux/man-pages/
- Readline Documentation: https://tiswww.case.edu/php/chet/readline/rltop.html
- Advanced Programming in the UNIX Environment (Stevens & Rago)
- The Linux Programming Interface (Kerrisk)

### How AI was used
AI tools were used as a support layer during development, mainly for:
- Reviewing edge cases for parser and redirection behavior.
- Clarifying POSIX/Bash behavioral differences for specific command scenarios.
- Suggesting test ideas and manual test matrices.
- Improving documentation wording and README organization.

AI was not used to replace understanding of core shell concepts.
Final design decisions, implementation, debugging, and validation were done manually.
