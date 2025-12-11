/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:30:19 by gajanvie          #+#    #+#             */
/*   Updated: 2025/12/11 12:34:56 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*join_path(char	*path, char *cmd)
{
	char	*result;
	char	*in_path;

	in_path = ft_strjoin(path, "/");
	if (!in_path)
		return (NULL);
	result = ft_strjoin(in_path, cmd);
	free(in_path);
	return (result);
}

char	*find_path_envp(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!(ft_strncmp("PATH=", envp[i], 5)))
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	**ft_setup_path(char **path, char **envp)
{
	char	*path_envp;

	path_envp = find_path_envp(envp);
	if (!path_envp)
		return (NULL);
	path = ft_split(path_envp, ':');
	return (path);
}

char	*getpath(char **envp, char *cmd)
{
	char	*test_path;
	char	**path;
	int		i;

	path = NULL;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	path = ft_setup_path(path, envp);
	if (!path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		test_path = join_path(path[i], cmd);
		if (test_path && access(test_path, X_OK) == 0)
		{
			free_all(path);
			return (test_path);
		}
		free(test_path);
		i++;
	}
	free_all(path);
	return (NULL);
}
