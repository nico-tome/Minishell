/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 00:13:56 by ntome             #+#    #+#             */
/*   Updated: 2025/12/12 18:15:50 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exit(t_minishell *ms, int print, char **cmd)
{
	(void)cmd;
	// cmd = "exit" "10" "NULL"
	if (ms->tokens)
		free_tokens(ms->tokens);
	if (ms->parsed_cmd)
		free_cmd_list(ms->parsed_cmd);
	if (ms->envp)
		free_env_list(ms->envp);
	if (ms->pwd)
		free(ms->pwd);
	if (print)
		printf("exit\n");
	rl_clear_history();
	exit(ms->status);
}
