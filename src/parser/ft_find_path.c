/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:30:19 by gajanvie          #+#    #+#             */
/*   Updated: 2025/12/11 23:44:28 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <minishell.h>

char	*join_path(char *path, char *cmd)
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

char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, sizeof(env->key)) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	**ft_setup_path(t_env *env)
{
	char	*path_value;
	char	**paths;

	path_value = get_env_value(env, "PATH");
	if (!path_value)
		return (NULL);
	paths = ft_split(path_value, ':');
	return (paths);
}

char	*ft_cmd_slash(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

char	*getpath(t_env *env, char *cmd)
{
	char	*test_path;
	char	**paths;
	int		i;

	if (cmd && ft_strchr(cmd, '/'))
		return (ft_cmd_slash(cmd));
	paths = ft_setup_path(env);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i++])
	{
		test_path = join_path(paths[i], cmd);
		if (test_path && access(test_path, X_OK) == 0)
		{
			free_all(paths);
			return (test_path);
		}
		free(test_path);
	}
	free_all(paths);
	return (NULL);
}
