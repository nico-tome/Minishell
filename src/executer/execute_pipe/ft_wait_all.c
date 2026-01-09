/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 15:58:51 by gajanvie          #+#    #+#             */
/*   Updated: 2026/01/09 18:51:44 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_pid_wait(int *exit_code, pid_t *pids, t_cmd *cmd, int i)
{
	int	status;

	waitpid(pids[i], &status, 0);
	if (cmd->next == NULL)
	{
		if (WTERMSIG(status) == SIGINT)
			ft_putchar_fd('\n', 1);
		if (WIFEXITED(status))
			*exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			*exit_code = 128 + WTERMSIG(status);
	}
}

void	wait_all(pid_t *pids, t_cmd *cmd, t_minishell *ms)
{
	int	i;
	int	exit_code;

	i = 0;
	exit_code = 0;
	while (cmd)
	{
		if (pids[i] != -1)
			handle_pid_wait(&exit_code, pids, cmd, i);
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

void	end_loop(int *prev_read, int *pipefd, t_cmd *curr)
{
	safe_close(*prev_read);
	if (curr->next)
	{
		safe_close(pipefd[1]);
		*prev_read = pipefd[0];
	}
	else
		*prev_read = -1;
	safe_close(curr->fd_in);
	safe_close(curr->fd_out);
}
