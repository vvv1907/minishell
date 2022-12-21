Minishell

(project of School 21)

This project should partially emulate the behavior of bash:

- have a working history of commands
- search and launch the right executable
- not interpret unclosed quotes or special characters such as \ (backslash) or ; (semicolon)
- handle ' (single quote) and " (double quote)
- implement redirections and pipes
- handle $? and following signals: ctrl-C, ctrl-D, ctrl-\
- implement some builtins such as echo, cd, pwd, export, unset, env, exit.
