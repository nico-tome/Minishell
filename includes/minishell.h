/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 12:31:35 by ntome             #+#    #+#             */
/*   Updated: 2025/12/17 13:29:04 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <stdint.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include <sys/types.h>
# include <sys/wait.h>

# define C1 "\033[38;5;129m"
# define C2 "\033[38;5;171m"
# define C3 "\033[38;5;210m"
# define C4 "\033[38;5;45m"
# define C5 "\033[32m"
# define C6 "\033[33m"
# define RESET "\033[0m"

extern int	g_exit_status;

typedef struct s_prompt_params
{
	int	exit_status;
	int	pwd;
}			t_prompt_params;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
	TOKEN_ERROR,
	END,
}				t_token_type;

typedef struct s_token
{
	char			*content;
	t_token_type	type;
	struct s_token	*next;
}				t_token;

typedef struct s_cmd
{
	char			**args;
	char			*cmd_path;
	int				fd_in;
	int				fd_out;
	int				status;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_double_index
{
	int	j;
	int	i;
}				t_double_index;

typedef struct s_minishell
{
	t_env			*envp;
	t_prompt_params	prompt_params;
	char			*pwd;
	t_token			*tokens;
	t_cmd			*parsed_cmd;
	int				status;
}				t_minishell;

typedef struct s_exec
{
	t_cmd		*cmd_list;
	t_env		*env_list;
	char		**env_tab;
	pid_t		*pids;
	int			count;
	t_minishell	*ms;
}				t_exec;

char			*ms_get_prompt(t_minishell ms);
t_prompt_params	ms_init_prompt_params(void);
void			ms_tokenize_cmd(t_token **token, char *cmd);
int				ms_has_error(t_token *token);
void			free_all(char **tab);
char			*getpath(t_env *env, char *cmd);
void			add_to_cmd(t_cmd *cmd, char *content, t_env *env);
t_cmd			*parser(t_token *tokens, t_env *env);
t_env			*init_env(char **envp);
void			exec_line(t_minishell *ms);
char			**list_to_tab(t_env *env);
void			free_cmd_list(t_cmd *cmd);
void			free_env_list(t_env *env);
int				check_pipe(t_token *token);
int				check_redirections(t_token *token);
void			free_tokens(t_token *token);
int				check_forbiden_char(char *word);
void			signal_handler(int signal);
void			ms_exit(t_minishell *ms, int print, char **cmd);
int				is_builtin(char *cmd);
void			exec_builtin(t_minishell *ms, int e_p, t_cmd *cmd, t_exec *e);
int				ft_tablen(char **tab);
int				cd(t_minishell *ms, t_cmd *cmd);
char			*get_env(t_env *envp, char *env);
void			update_env_val(t_env *env, char *key, char *new_val);
int				ms_has_error(t_token *token);
int				is_quote_redir(char c);
void			ms_get_word_redir(char *cmd, int *i, int *start);
void			ms_get_word_quote(char *cmd, int *i, int *start);
void			ms_get_word(char *cmd, int *i, int *start);
void			ms_pwd(void);
void			ms_env(t_minishell *ms);
int				ft_unset(t_minishell *ms, char **args);
void			ms_echo(t_minishell *ms, t_cmd *cmd);
void			ms_print_hello(void);
void			wait_all(pid_t *pids, int count, t_minishell *ms);
char			*ft_join_value(char *key, char *value);
void			dup2_and_close(int fd, int target_fd);
void			safe_close(int fd);
void			ft_exit_child(t_exec *exec, int exit_code);
void			ft_free_exec(t_exec *exec);
void			init_exec(t_exec *exec, t_minishell *ms);
int				ft_env_size(t_env *env);
int				init_cd(int *print_path, t_cmd *cmd, int *should_free);
int				switch_dir(char *path, int should_free, int print_path);
t_cmd			*create_new_cmd(void);
void			ft_env_add_back(t_env **lst, t_env *new);
t_env			*ft_env_new(char *str);
int				ms_export(t_minishell *ms, t_cmd *cmd);
t_env			*get_env_node(t_env *envp, char *env);
char			*ft_rand_name(void);
char			*ft_remove_quotes(char *str);
char			*ft_expand_arg(t_minishell *ms, char *str);
int				gajanvie(char **cmd);
int				ntome(char **cmd);
void			print_latina(void);
int				gamble(void);
void			make_printable(char *c);

#endif
