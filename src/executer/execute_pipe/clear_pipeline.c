/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 16:02:05 by gajanvie          #+#    #+#             */
/*   Updated: 2025/12/13 17:04:21 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	safe_close(int fd)
{
	if (fd > 2)
		close(fd);
}

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->args)
			free_all(cmd->args);
		if (cmd->cmd_path)
			free(cmd->cmd_path);
		safe_close(cmd->fd_in);
		safe_close(cmd->fd_out);
		free(cmd);
		cmd = tmp;
	}
}

void	ft_free_exec(t_exec *exec)
{
	if (exec->env_tab)
		free_all(exec->env_tab);
	if (exec->pids)
		free(exec->pids);
}

void	ft_exit_child(t_exec *exec, int exit_code)
{
	ft_free_exec(exec);
	if (exec->cmd_list)
		free_cmd_list(exec->cmd_list);
	if (exec->env_list)
		free_env_list(exec->env_list);
	if (exec->ms->tokens)
		free_tokens(exec->ms->tokens);
	if (exec->ms->pwd)
		free(exec->ms->pwd);
	rl_clear_history();
	exit(exit_code);
}

void	dup2_and_close(int fd, int target_fd)
{
	if (dup2(fd, target_fd) == -1)
	{
		perror("dup2");
		exit(EXIT_FAILURE);
	}
	close(fd);
}
