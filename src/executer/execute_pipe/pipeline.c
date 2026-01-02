/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:52:15 by gajanvie          #+#    #+#             */
/*   Updated: 2026/01/02 15:47:46 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exec_external(t_cmd *cmd, t_exec *exec)
{
	if (!cmd->cmd_path || !ft_strcmp(cmd->args[0], "..") || !ft_strcmp(cmd->args[0], "."))
	{
		ft_putstr_fd("Minishell: command not found: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd("\n", 2);
		ft_exit_child(exec, 127);
	}
	execve(cmd->cmd_path, cmd->args, exec->env_tab);
	perror("execve");
	ft_exit_child(exec, 126);
}

void	handle_pipes(t_cmd *cmd, int prev_read, int pipefd[2])
{
	if (cmd->fd_in > -1)
	{
		dup2_and_close(cmd->fd_in, STDIN_FILENO);
		if (prev_read != -1)
			close(prev_read);
	}
	else if (prev_read != -1)
		dup2_and_close(prev_read, STDIN_FILENO);
	if (cmd->fd_out > -1)
		dup2_and_close(cmd->fd_out, STDOUT_FILENO);
	else if (cmd->next != NULL)
		dup2(pipefd[1], STDOUT_FILENO);
	safe_close(pipefd[0]);
	safe_close(pipefd[1]);
}

void	child_process(t_cmd *cmd, t_exec *exec, int *pipefd, int prev_read)
{
	if (cmd->status == 1)
	{
		safe_close(pipefd[1]);
		safe_close(pipefd[0]);
		safe_close(prev_read);
		ft_exit_child(exec, 1);
	}
	if (!cmd->args || !cmd->args[0])
	{
		safe_close(pipefd[1]);
		safe_close(pipefd[0]);
		safe_close(prev_read);
		ft_exit_child(exec, 0);
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	handle_pipes(cmd, prev_read, pipefd);
	if (is_builtin(cmd->args[0]))
	{
		exec_builtin(exec->ms, 0, cmd, exec);
		ft_exit_child(exec, 0);
	}
	exec_external(cmd, exec);
}

void	exec_loop(t_exec *exec, t_cmd *curr, int *pipefd, int *prev_read)
{
	int	i;

	i = 0;
	while (curr)
	{
		pipefd[0] = -1;
		pipefd[1] = -1;
		if (curr->next && pipe(pipefd) == -1)
			perror("pipe");
		exec->pids[i] = fork();
		if (exec->pids[i] == 0)
			child_process(curr, exec, pipefd, *prev_read);
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
		curr = curr->next;
		i++;
	}
}

void	exec_line(t_minishell *ms)
{
	t_exec	exec;
	int		pipefd[2];
	int		prev_read;

	prev_read = -1;
	init_exec(&exec, ms);
	if (!exec.pids || !exec.env_tab)
	{
		ft_free_exec(&exec);
		return ;
	}
	signal(SIGINT, SIG_IGN);
	exec_loop(&exec, ms->parsed_cmd, pipefd, &prev_read);
	wait_all(exec.pids, exec.count, ms);
	signal(SIGINT, signal_handler);
	ft_free_exec(&exec);
}
