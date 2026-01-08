/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titan <titan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 15:58:51 by gajanvie          #+#    #+#             */
/*   Updated: 2026/01/08 21:53:17 by titan            ###   ########.fr       */
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
		if (pids[i] != -1)
		{
			waitpid(pids[i], &status, 0);
			if (cmd->next == NULL)
			{
				if (WTERMSIG(status) == SIGINT)
					ft_putchar_fd('\n', 1);
				if (WIFEXITED(status))
					exit_code = WEXITSTATUS(status);
				else if (WIFSIGNALED(status))
					exit_code = 128 + WTERMSIG(status);
			}
		}
		else
		{
			if (cmd->next == NULL)
				exit_code = cmd->status;
		}
		i++;
		cmd = cmd->next;
	}
	ms->status = exit_code;
}
