This project has been created as part of the 42 curriculum by vgotzlov, msnizek.

# Minishell

# Description

"As beautiful as a shell." This project is part of the 42 school curriculum (42 Prague). The goal was to create our own fully functional Unix shell from scratch, inspired by Bash, using the C programming language and adhering to strict coding standards (Norminette). The main architecture could be divided to four parts, Lexing, Parsing, Expansion and Execution

# Instructions

Compilation is handled via the provided Makefile. The project requires the readline library to be installed on your system.

Clone the repository

> git clone <repository_url> minishell

> cd minishell

Compile the project
>make

Run the interactive shell
>./minishell


# Resources

Bash Reference Manual - Main reference for shell behavior.

GNU Readline Documentation

Minishell: Building a mini-bash (Medium)

AI Usage: Gemini - used for code overview and testing

# Feature List

The project fully supports the following features:

Prompt: Displays an interactive prompt while waiting for a new command.

History: Ability to navigate through previous commands using arrow keys (via readline).

Path Execution: Searches and executes programs based on the $PATH environment variable, or via relative/absolute paths.

*Quotes:*

' ' (Single quotes): Prevents the interpretation of all meta-characters.

" " (Double quotes): Prevents interpretation with the exception of $ (variable expansion).

*Redirections:*

< redirects input.

*>* redirects output (overwrites file).

<< (Here-doc) reads input from the user until the specified delimiter is reached.

*>>* redirects output (appends to file).

*Pipes:* | connects the output of one command to the input of the next.

Environment Variables: Expansion using the $ character.

*Signals:*

ctrl-C: Prints a new line and displays a fresh prompt.

ctrl-D: Correctly exits the shell (EOF).

ctrl-\: Does nothing (ignored), matching standard Bash behavior.

# Builtins

The shell implements the following builtins without calling external binaries:

echo (including the -n flag)

cd (with relative or absolute paths)

pwd (prints the current working directory)

export (adds or modifies environment variables)

unset (removes environment variables)

env (prints environment variables)

exit (exits the shell with a specified numerical status)