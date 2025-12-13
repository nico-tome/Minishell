/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 15:57:29 by gajanvie          #+#    #+#             */
/*   Updated: 2025/12/13 15:57:55 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_builtin(char *cmd)
{
	if (!ft_strcmp("exit", cmd) || !ft_strcmp("cd", cmd))
		return (1);
	else if (!ft_strcmp("echo", cmd) || !ft_strcmp("pwd", cmd))
		return (1);
	else if (!ft_strcmp("export", cmd) || !ft_strcmp("env", cmd))
		return (1);
	else if (!ft_strcmp("ms_header", cmd))
		return (1);
	else if (!ft_strcmp("set_prompt_exit", cmd))
		return (1);
	else if (!ft_strcmp("ntome", cmd)
		|| !ft_strcmp("gajanvie", cmd))
		return (1);
	else if (!ft_strcmp("unset", cmd))
		return (1);
	return (0);
}

void	exec_builtin(t_minishell *ms, int exit_print, t_cmd *cmd, t_exec *exec)
{
	char			*cmd_name;

	cmd_name = cmd->args[0];
	if (!ft_strcmp(cmd_name, "exit"))
	{
		if (exec)
			ft_free_exec(exec);
		ms_exit(ms, exit_print, cmd->args);
	}
	if (!ft_strcmp(cmd_name, "cd"))
		g_exit_status = cd(ms, cmd);
	if (!ft_strcmp(cmd_name, "pwd"))
		ms_pwd();
	if (!ft_strcmp(cmd_name, "env"))
		ms_env(ms);
	if (!ft_strcmp(cmd_name, "unset"))
		ft_unset(ms, cmd->args);
	if (!ft_strcmp(cmd_name, "echo"))
		ms_echo(ms, cmd);
	if (!ft_strcmp(cmd_name, "ms_header"))
		ms_print_hello();
}
