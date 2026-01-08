/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 13:55:12 by ntome             #+#    #+#             */
/*   Updated: 2026/01/08 09:46:18 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <minishell.h>

int	is_valide_env(t_minishell *ms, char *env)
{
	char	*value;

	value = get_env(ms->envp, env);
	if (!value)
		return (0);
	free(value);
	return (1);
}

int	is_option_n(char *option)
{
	int	i;

	if (!ft_strcmp(option, "-n"))
		return (1);
	if (!ft_strncmp(option, "-n", 2))
	{
		i = 2;
		while (option[i] == 'n')
			i++;
		if (option[i] == '\0')
			return (1);
	}
	return (0);
}

int	ms_echo(t_cmd *cmd)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	if (cmd->fd_out == -2)
		cmd->fd_out = 1;
	while (cmd->args[i] && is_option_n(cmd->args[i]))
	{
		new_line = 0;
		i++;
	}
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], cmd->fd_out);
		i++;
		if (cmd->args[i])
			ft_putstr_fd(" ", cmd->fd_out);
	}
	if (new_line)
		ft_putstr_fd("\n", cmd->fd_out);
	return (0);
}
