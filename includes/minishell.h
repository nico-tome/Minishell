/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 12:31:35 by ntome             #+#    #+#             */
/*   Updated: 2025/12/11 12:36:21 by gajanvie         ###   ########.fr       */
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

extern int g_exit_status;

typedef struct s_prompt_params
{
	int	time;
	int	exit_status;
	int	pwd;
}			t_prompt_params;

typedef struct s_minishell
{
	char			**envp;
	t_prompt_params	prompt_params;
	int				exit_status;
	char			*pwd;
}				t_minishell;

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

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_exec
{
	t_cmd	*cmd_list;
	t_env	*env_list;
	char	**env_tab;
	pid_t	*pids;
	int		count;
}				t_exec;

char			*ms_get_prompt(t_minishell ms);
t_prompt_params	ms_init_prompt_params(void);
void			ms_tokenize_cmd(t_token **token, char *cmd);
int				ms_has_error(t_token *token);
void			free_all(char **tab);
char			*getpath(char **envp, char *cmd);

#endif
