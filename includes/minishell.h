/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 12:31:35 by ntome             #+#    #+#             */
/*   Updated: 2025/12/10 00:36:11 by ntome            ###   ########.fr       */
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

char			*ms_get_prompt(t_minishell ms);
t_prompt_params	ms_init_prompt_params(void);

#endif
