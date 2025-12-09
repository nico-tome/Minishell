# 🐚 Minishell

## TODO

[] gerer les signaux
[] faire le pre parsing

## 📃 Parts of a Shell Program

The shell implementation is divided into three parts: 
- Lexer
- Parser
- Expander
- Executor

---

### The Lexer

The lexer will do the lexical analyze of the command. He will read the charachters one by one and create tokens that will be passed to the parser. [Here](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html#tag_02_03) a good article about shell grammar.

---

### The parser

The Parser is the software component that reads the command line such as `ls ­al | grep me > file1` and puts it 
into a data structure called **Command Table** that will store the commands that will be 
executed.

__Simple Command array__
| 0:  |  ls  | -al  | NULL |
|-----|------|------|------|
| 1:  | grep |  me  | NULL |

__IO REDIRECTION__
| in: default | out: file1 | err: default |
|-------------|------------|--------------|

In code it will look like this:
```h
typedef struct s_simplecommand
{
  int  args_count;
  char **args;
}            t_simplecommand;
```
