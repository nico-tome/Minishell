/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 15:52:15 by gajanvie          #+#    #+#             */
/*   Updated: 2025/12/12 18:20:21 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	safe_close(int fd)
{
	if (fd > 2)
		close(fd);
}

void	free_env_list(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		if (env->key)
			free(env->key);
		if (env->value)
			free(env->value);
		free(env);
		env = tmp;
	}
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
	exit(exit_code);
}

void	exec_external(t_cmd *cmd, t_exec *exec)
{
	if (!cmd->cmd_path)
	{
		ft_putstr_fd("Minishell: command not found: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd("\n", 2);
		ft_exit_child(exec, 127);
	}
	execve(cmd->cmd_path, cmd->args, exec->env_tab);
	perror("execve");
	free(cmd->cmd_path);
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

int	is_builtin(char *cmd)
{
	int	size;

	size = ft_strlen(cmd);
	if (!ft_strncmp("exit", cmd, size) || !ft_strncmp("cd", cmd, size))
		return (1);
	else if (!ft_strncmp("echo", cmd, size) || !ft_strncmp("pwd", cmd, size))
		return (1);
	else if (!ft_strncmp("export", cmd, size) || !ft_strncmp("env", cmd, size))
		return (1);
	else if (!ft_strncmp("ms_header", cmd, size))
		return (1);
	else if (!ft_strncmp("set_prompt_exit", cmd, size))
		return (1);
	else if (!ft_strncmp("ntome", cmd, size)
		|| !ft_strncmp("gajanvie", cmd, size))
		return (1);
	return (0);
}

void	exec_builtin(t_minishell *ms, int exit_print, t_cmd *cmd, t_exec *exec)
{
	unsigned long	size;

	size = sizeof(ms->parsed_cmd->args[0]);
	if (!ft_strncmp(ms->parsed_cmd->args[0], "exit", size))
	{
		if (exec)
			ft_free_exec(exec);
		ms_exit(ms, exit_print, cmd->args);
	}
	if (!ft_strncmp(ms->parsed_cmd->args[0], "cd", size))
		ms->status = cd(ms, ms->parsed_cmd);
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
	handle_pipes(cmd, prev_read, pipefd);
	if (is_builtin(cmd->args[0]))
	{
		exec_builtin(exec->ms, 0, cmd, exec);
		ft_exit_child(exec, 0);
	}
	exec_external(cmd, exec);
}

int	count_cmds(t_cmd *cmd)
{
	int	result;

	result = 0;
	while (cmd)
	{
		result++;
		cmd = cmd->next;
	}
	return (result);
}

void	init_exec(t_exec *exec, t_minishell *ms)
{
	exec->cmd_list = ms->parsed_cmd;
	exec->env_list = ms->envp;
	exec->count = count_cmds(ms->parsed_cmd);
	exec->env_tab = list_to_tab(ms->envp);
	exec->pids = malloc(sizeof(pid_t) * exec->count);
	exec->ms = ms;
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
	exec_loop(&exec, ms->parsed_cmd, pipefd, &prev_read);
	wait_all(exec.pids, exec.count);
	ft_free_exec(&exec);
}
