/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 23:38:09 by ntome             #+#    #+#             */
/*   Updated: 2025/12/19 16:54:12 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <minishell.h>

int	is_valid_export_key(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	if (str[i] == '+')
	{
		if (!str[i + 1])
			return (0);
		if (str[i + 1] != '=')
			return (0);
	}
	return (1);
}

int	add_or_update_env(t_minishell *ms, char *key, char *value)
{
	t_env	*old_env;

	old_env = get_env_node(ms->envp, key);
	if (old_env && ft_strcmp(key, "_"))
	{
		if (value)
		{
			if (!value)
				return (1);
			if (old_env->value)
				free(old_env->value);
			old_env->value = ft_strdup(value);
		}
	}
	else if (ft_strcmp(key, "_"))
	{
		old_env = ft_env_new(key);
		if (!old_env)
			return (1);
		if (value)
			old_env->value = ft_strdup(value);
		ft_env_add_back(&ms->envp, old_env);
	}
	return (0);
}

int	join_env(t_minishell *ms, char *key, char *value)
{
	t_env	*old_env;
	char	*tmp;

	old_env = get_env_node(ms->envp, key);
	if (old_env && ft_strcmp(key, "_"))
	{
		if (value)
		{
			tmp = old_env->value;
			old_env->value = ft_strjoin(old_env->value, value);
			free(tmp);
		}
	}
	else if (ft_strcmp(key, "_"))
	{
		old_env = ft_env_new(key);
		if (!old_env)
			return (1);
		if (value)
			old_env->value = ft_strdup(value);
		ft_env_add_back(&ms->envp, old_env);
	}
	return (0);
}

int	process_export_arg(t_minishell *ms, char *arg, int join)
{
	char	*equal;
	char	*key;
	char	*value;
	int		ret;

	equal = ft_strchr(arg, '=');
	value = NULL;
	if (!equal)
		key = ft_strdup(arg);
	else
	{
		*(equal - join) = '\0';
		key = ft_strdup(arg);
		value = ft_strdup(equal + 1);
		*equal = '=';
	}
	if (!key || (equal && !value))
		return (free(key), free(value), 1);
	if (join)
		ret = join_env(ms, key, value);
	else
		ret = add_or_update_env(ms, key, value);
	free(key);
	if (value)
		free(value);
	return (ret);
}

int	ms_export(t_minishell *ms, t_cmd *cmd)
{
	int		i;
	int		ret;

	ret = 0;
	if (ft_tablen(cmd->args) == 1)
	{
		print_export_values(ms);
		return (0);
	}
	i = 0;
	while (cmd->args[++i])
	{
		if (!is_valid_export_key(cmd->args[i]))
			ret = print_export_error(cmd->args[i]);
		else
		{
			if (!ft_strchr(cmd->args[i], '+'))
				ret += process_export_arg(ms, cmd->args[i], 0);
			else
				ret += process_export_arg(ms, cmd->args[i], 1);
		}
	}
	ms->status = ret;
	return (ret > 0);
}
