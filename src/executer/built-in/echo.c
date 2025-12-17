/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 13:55:12 by ntome             #+#    #+#             */
/*   Updated: 2025/12/17 21:02:48 by ntome            ###   ########.fr       */
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

void	ms_echo(t_cmd *cmd)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	while (cmd->args[i] && !ft_strcmp(cmd->args[i], "-n"))
	{
		new_line = 0;
		i++;
	}
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		i++;
		if (cmd->args[i])
			printf(" ");
	}
	if (new_line)
		printf("\n");
}
