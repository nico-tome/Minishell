/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titan <titan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 23:38:09 by ntome             #+#    #+#             */
/*   Updated: 2025/12/15 10:49:29 by ntome            ###   ########.fr       */
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
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
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

void	print_export_values(t_minishell *ms)
{
	(void)ms;
	//la soit on transforme la liste en char** et c'est plus facile a sort mais faut bien gerer les free.
	//soit on loop a travers la struct et faut réussir a sort mais là j'y arrive pas j'ai le cerveau mort mdrr.
}

int	ms_export(t_minishell *ms, t_cmd *cmd)
{
	int		i;
	char	*equal;
	char	*key;
	char	*value;
	int		ret;

	if (ft_tablen(cmd->args) == 1)
	{
		print_export_values(ms);
		return (0);
	}
	i = 1;
	while (cmd->args[i])
	{
		if (!is_valid_export_key(cmd->args[i]))
		{
			ft_putstr_fd("Minishell: export: `", 2);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			ms->status = 1;
		}
		else
		{
			equal = ft_strchr(cmd->args[i], '=');
			if (!equal)
			{
				key = ft_strdup(cmd->args[i]);
				value = NULL;
			}
			else
			{
				*equal = '\0';
				key = ft_strdup(cmd->args[i]);
				value = ft_strdup(equal + 1);
				*equal = '=';
			}
			if (!key || (equal && !value))
			{
				if (key)
					free(key);
				if (value)
					free(value);
				ft_putstr_fd("Minishell: malloc error in export\n", 2);
				return (1);
			}
			ret = add_or_update_env(ms, key, value);
			if (key)
				free(key);
			if (value)
				free(value);
			if (ret != 0)
			{
				ft_putstr_fd("Minishell: malloc error in export\n", 2);
				return (1);
			}
		}
		i++;
	}
	return (ms->status);
}
