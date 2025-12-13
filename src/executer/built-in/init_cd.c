/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 16:29:34 by gajanvie          #+#    #+#             */
/*   Updated: 2025/12/13 16:40:40 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	switch_dir(char *path, int should_free, int print_path)
{
	if (!path || chdir(path) == -1)
	{
		if (path)
		{
			ft_putstr_fd("Minishell: cd: ", 2);
			perror(path);
		}
		if (should_free)
			free(path);
		return (1);
	}
	if (print_path)
		printf("%s\n", path);
	return (0);
}

int	init_cd(int *print_path, t_cmd *cmd, int *should_free)
{
	*print_path = 0;
	*should_free = 0;
	if (ft_tablen(cmd->args) > 2)
	{
		ft_putstr_fd("Minishell: cd: too many arguments\n", 2);
		return (1);
	}
	return (0);
}
