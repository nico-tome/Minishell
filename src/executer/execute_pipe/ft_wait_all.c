/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 15:58:51 by gajanvie          #+#    #+#             */
/*   Updated: 2025/12/13 15:59:16 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	update_exit_status(int code)
{
	g_exit_status = code;
}

void	wait_all(pid_t *pids, int count)
{
	int	i;
	int	status;
	int	exit_code;

	i = 0;
	exit_code = 0;
	while (i < count)
	{
		waitpid(pids[i], &status, 0);
		if (i == count - 1)
		{
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_code = 128 + WTERMSIG(status);
		}
		i++;
	}
	update_exit_status(exit_code);
}
