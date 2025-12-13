/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 15:32:47 by gajanvie          #+#    #+#             */
/*   Updated: 2025/12/13 16:01:01 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env_val(t_env *env, char *key, char *new_val)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(env->key)) == 0)
		{
			if (env->value)
				free(env->value);
			env->value = ft_strdup(new_val);
			return ;
		}
		env = env->next;
	}
}

int	ft_env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	*ft_join_value(char *key, char *value)
{
	char			*str;
	int				len_k;
	int				len_v;
	t_double_index	index;

	if (!key)
		return (NULL);
	len_k = ft_strlen(key);
	len_v = ft_strlen(value);
	str = malloc(sizeof(char) * (len_k + len_v + 2));
	if (!str)
		return (NULL);
	index.i = -1;
	while (++index.i < len_k)
		str[index.i] = key[index.i];
	str[index.i++] = '=';
	index.j = 0;
	while (value && value[index.j])
		str[index.i++] = value[index.j++];
	str[index.i] = '\0';
	return (str);
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

char	*get_env(t_env *envp, char *env)
{
	while (envp)
	{
		if (!ft_strncmp(env, envp->key, ft_strlen(env)))
			return (envp->value);
		envp = envp->next;
	}
	return (NULL);
}
