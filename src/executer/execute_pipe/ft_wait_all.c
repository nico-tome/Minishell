/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 15:58:51 by gajanvie          #+#    #+#             */
/*   Updated: 2026/01/08 20:39:58 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	wait_all(pid_t *pids, t_cmd *cmd, t_minishell *ms)
{
	int	i;
	int	status;
	int	exit_code;

	i = 0;
	exit_code = 0;
	while (cmd)
	{
		waitpid(pids[i++], &status, 0);
		if (cmd->next == NULL)
		{
			if (WTERMSIG(status) == SIGINT)
			{
				if (cmd->fd_out == -2)
					cmd->fd_out = 1;
				ft_putchar_fd('\n', cmd->fd_out);
			}
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_code = 128 + WTERMSIG(status);
		}
		cmd = cmd->next;
	}
	ms->status = exit_code;
}
