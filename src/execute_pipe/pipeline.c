/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:52:15 by gajanvie          #+#    #+#             */
/*   Updated: 2025/12/10 18:44:11 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	safe_close(int fd)
{
	if (fd > 2)
		close(fd);
}

void	ft_free_exec(t_exec *exec)
{
	if (exec->env_tab)
		free_tab(exec->env_tab);
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
	exit(exit_code);
}

void	exec_external(t_cmd *cmd, t_exec *exec)
{
	char    *path;

	path = getpath(exec->env_tab, cmd->args[0]);
	if (!path)
	{
		ft_putstr_fd("Minishell: command not found: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd("\n", 2);
		ft_exit_child(exec, 127);
	}
	execve(path, cmd->args, exec->env_tab);
	perror("execve");
	free(path);
	ft_exit_child(exec, 126);
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

void	handle_pipes_and_redirs(t_cmd *cmd, int prev_read, int pipefd[2])
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
	close(pipefd[0]);
	close(pipefd[1]);
}

void	child_process(t_cmd *cmd, t_exec *exec, int *pipefd, int prev_read)
{
	handle_pipes_and_redirs(cmd, prev_read, pipefd);
	if (is_builtin(cmd->args[0]))
	{
		exec_builtin(cmd, exec->env_list);
		ft_exit_child(exec, 0);
	}
	exec_external(cmd, exec);
}

void	init_exec(t_exec *exec, t_cmd *cmd, t_env *env)
{
	exec->cmd_list = cmd;
	exec->env_list = env;
	exec->count = count_cmds(cmd);
	exec->env_tab = list_to_tab(env);
	exec->pids = malloc(sizeof(pid_t) * exec->count);
}

void	exec_loop(t_exec *exec, t_cmd *curr, int *pipefd, int *prev_read)
{
	int	i;

	i = 0;
	while (curr)
	{
		if (curr->next && pipe(pipefd) == -1)
			perror("pipe");
		exec->pids[i] = fork();
		if (exec->pids[i] == 0)
			child_process(curr, exec, pipefd, *prev_read);
		if (*prev_read != -1)
			close(*prev_read);
		if (curr->next)
		{
			close(pipefd[1]);
			*prev_read = pipefd[0];
		}
		else
			*prev_read = -1;
		if (curr->fd_in > 2)
			close(curr->fd_in);
		if (curr->fd_out > 2)
			close(curr->fd_out);
		curr = curr->next;
		i++;
	}
}

void	exec_line(t_cmd *cmd, t_env *env)
{
	t_exec	exec;
	int		pipefd[2];
	int		prev_read;

	prev_read = -1;
	init_exec(&exec, cmd, env);
	if (!exec.pids || !exec.env_tab)
	{
		ft_free_exec(&exec);
		return ;
	}
	exec_loop(&exec, cmd, pipefd, &prev_read);
	wait_all_and_update_exit_status(exec.pids, exec.count, env);
	ft_free_exec(&exec);
}
