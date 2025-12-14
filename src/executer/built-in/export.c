/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titan <titan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 23:38:09 by ntome             #+#    #+#             */
/*   Updated: 2025/12/14 19:32:07 by titan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_valid_key(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	add_or_update_env(t_minishell *ms, char *key, char *value)
{
	t_env	*new_node;
	char	*new_val;

	new_node = get_env(ms->envp, key);
	if (new_node)
	{
		if (value)
		{
			new_val = ft_strdup(value);
			if (!new_val)
				return (1);
			if (new_node->value)
				free(new_node->value);
			new_node->value = ft_strdup(value);
		}
	}
	else
	{
		//new_node = ft_lstnewenvp(key, value); faut la code parce que ft_new_env marche pas avec key value
		if (!new_node)
			return (1);
		ft_env_add_back(&ms->envp, new_node);
	}
	return (0);
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
		//afficher dans l'ordre alphabetique
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
