# 🐚 Minishell

## 📑 TODO

Fonction et code:

- [x] faire le pre parsing -> split en token
- [x] check la synthax
- [x] executer la command, si redirection executer dans le bon ordre
- [x] stock les datas
- [x] free les datas quand on sort du shell

Demande du sujet:

- [x] Display a prompt
- [x] Have a working history
- [x] Search and launch the right executable
- [ ] Have a signal handler
- [ ] Ignore command with ; and \
- [x] Handle ' and "
- [ ] Execute $cmd in double quote
- [x] Redirections:
  - [x] <
  - [x] >
  - [x] <<
  - [x] >>
- [x] Pipes
- [ ] Environement variables
- [ ] $? (exit status of last cmd
- [ ] Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
- [ ] Handle ctrl-C ctrl-D and ctrl-\
- [ ] Built ins:
  - [ ] echo -n
  - [ ] cd
  - [ ] pwd
  - [ ] export
  - [ ] unset
  - [ ] env
  - [ ] exit

## Function and utility

- readline
- rl_clear_history
- rl_on_new_line
- rl_replace_line
- rl_redisplay
- add_history -> usefull to manage cmd history
- printf
- malloc
- free
- write
- access -> use to check acces to a file, a directory or a program
- open, read, close -> usefull for redirection like `<`  or `>`
- fork -> usefull when launching a program (ex: ./minishell in minishell)
- wait, waitpid, wait3, wait4 -> usefull for pipe
- signal, sigaction, sigemptyset, sigaddset, kill -> signal handle (exit status, ctrl-C etc...)
- exit -> exit minishell
- getcwd -> use to get the directory
- chdir -> change directory
- stat, lstat, fstat -> return informations about a file, usefull for execution ?
- unlink -> delet a file (like rm)
- execve -> execute a program, usefull for execution
- dup, dup2 -> create a new fd of a file, usefull for redirection
- pipe -> create a pipe, usefull for pipe
- opendir, readdir, closedir -> manipulate directory, usefull for execution
- strerror, perror -> usefull for error messages, after parsing
- isatty, ttyname, ttyslot -> check if fd is terminal and get infos
- ioctl -> ?
- getenv -> get environement varaible name
- tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs -> usefull for parsing and tokenizer

## 📃 Parts of a Shell Program

The shell implementation is divided into three parts: 
- Lexer (pre parsing -> tokenize)
- Parser
- Executor

---
