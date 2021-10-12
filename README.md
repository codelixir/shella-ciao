# Shella Ciao

[![forthebadge](https://forthebadge.com/images/badges/made-with-c.svg)](https://forthebadge.com)

## Running the Shell

```sh
$ cd code
$ make
...
$ ./a.out
```

## Commands and other features

`cd`, `echo`, `exit`, `ls`, `pinfo`, `pwd`, `repeat`, `jobs`, `sig`, `fg`, `bg` and system commands (`vi`, `subl`, etc)

- Piping ( `cmd1 | cmd 2 `  etc.)
- Redirection ( `cmd < input_file >> output_file`  etc.)
- Keyboard interrupts (`Ctrl+C`, `Ctrl+D`, etc.)

For knowing more about how the 'user-defined' commands work (commands which are different from standard bash/zsh commands), you can check [Part 1](Assignment%20Part%201.pdf) for `pinfo` or `repeat`, and [Part 2](Assignment%20Part%202.pdf) for `jobs`, `sig`, `fg` or `bg`.

## Code Files

| Files                 | Description |
| --------------------- | ----------- |
| bg.c, bg.h | Implementing the user defined `bg` command |
| cd.c, cd.h            | Implementing the `cd` command (navigate to a directory). The command takes up to one argument. |
| echo.c, echo.h        | Implementing the `echo` command (printing to the console). Tabs and multiple spaces are handled.        |
| execute.c, execute.h  | Contains the function for handling all commands and calling the respective functions. **This also takes care of any redirects like >, >>, <**        |
| fg.c, fg.g | Implementing the user defined `fg` function.|
| headers.h | Including all external header files          |
| handlers.c, handlers.h | Contains custom defined signal handler functions. Includes handlers for ^C, ^Z and background processes. |
| jobs.c, jobs.h | Implementation for user defined `jobs` command. Takes the flags `-s`, `-r`, `-sr`, `-rs`. If no flags are given, defaults to `rs` mode. |
| ls.c, ls.h | Implementing `ls` including multiple arguments (both files and directories) and flags `-l` and `-a`.         |
| main.c | The main function of the program. After initializing the shell, it reads input from the user, adds it to history, tokenizes it into commands, and sends it into the `execute` function (`execute.c`)            |
| pinfo.c, pinfo.h      | Implementing the user-defined `pinfo` command. It takes information about the process from `/proc` directory and prints selected information on the terminal.        |
| pipe.c, pipe.h | Implements piping. Contains a `master` function which is called recursively to take care of everything including multiple piping and any combination of piping and redirection. |
| prompt.c, prompt.h    | Controls the shell prompt, for example, ```<pahulpreetsingh@MacBook-Pro:~/>``` Here, `~` is the directory from which the shell is executed.        |
| pwd.c, pwd.h          | Implements `pwd` command (prints present working directory)        |
| redirection.c, redirection.h | Includes a function called `check_redirection` which is called from within `execute`. Before the commands are executed, this simplifies the command and reallocates stdin/stdout according to the specified symbols (`>/>>/<`). |
| repeat.c, repeat.h    | Implements `repeat` command (`repeat n [cmd]`)        |
| sig.c, sig.h | Implements the user defined `sig` command (`sig [jobnum] [signum]`) |
| syscom.c, syscom.h    | Implementing system commands using `execvp()`        |
| utils.c, utils.h      | Some utility functions that I use across files, for example `untildefy()` and `tildefy()` (converts path relative to `~` to absolute path, and vice versa), and other functions.        |

## Assumptions

| Feature/String | Limits |
| -------------- | ------------- |
| All paths      | 1024 chars |
| User input     | 256 chars, 32 commands |
| Command arguments        | 32 (excluding flags) |

(For in-built commands) There are some commands that work *slightly* differently on different versions of bash and zsh. In such cases, I have followed the behavior of bash-3.2.

---
*This was built as a part of the Operating Systems and Networks course, Monsoon 2021.*