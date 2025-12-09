# 🐚 Minishell

## 📑 TODO

Fonction et code:

- [ ] faire le pre parsing -> split en token
- [ ] check la synthax
- [ ] executer la command, si redirection executer dans le bon ordre
- [ ] stock les datas
- [ ] free les datas quand on sort du shell

Demande du sujet:

- [ ] Display a prompt
- [ ] Have a working history
- [ ] Search and launch the right executable
- [ ] Have a signal handler
- [ ] Ignore command with ; and \
- [ ] Handle ' and "
- [ ] Execute $cmd in double quote
- [ ] Redirections:
  - [ ] <
  - [ ] >
  - [ ] <<
  - [ ] >>
- [ ] Pipes
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

## 📃 Parts of a Shell Program

The shell implementation is divided into three parts: 
- Lexer (pre parsing -> tokenize)
- Parser
- Executor

---
