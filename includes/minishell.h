/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 12:31:35 by ntome             #+#    #+#             */
/*   Updated: 2025/12/10 11:23:57 by gajanvie         ###   ########.fr       */
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
	APPEND
}				t_token_type;

typedef struct s_token
{
    char				*content;
    t_token_type		type;
    struct s_token		*next;
}				t_token;

typedef struct s_cmd
{
    char			**args;
    char			*cmd_path;
    int				fd_in;
    int				fd_out;
    struct s_cmd	*next;
}				t_cmd;

char			*ms_get_prompt(t_minishell ms);
t_prompt_params	ms_init_prompt_params(void);

#endif
