/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 23:38:09 by ntome             #+#    #+#             */
/*   Updated: 2025/12/16 15:08:13 by gajanvie         ###   ########.fr       */
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

char	*get_new_value(t_minishell *ms, char *value)
{
	char	*new_value;
	char	*expand;

	if (!value)
		return (NULL);
	if (value[0] == '"' || value[0] == '\'')
		new_value = ft_substr(value, 1, ft_strlen(value) - 2);
	if (!new_value)
		return (NULL);
	if (new_value[0] == '$')
	{
		expand = get_env(ms->envp, )
	}
}

int	add_or_update_env(t_minishell *ms, char *key, char *value)
{
	t_env	*old_env;
	char	*new_value;

	if (value)
		new_value = get_new_value(value);
	old_env = get_env_node(ms->envp, key);
	if (old_env && ft_strcmp(key, "_"))
	{
		if (value)
		{
			if (!value)
				return (1);
			if (old_env->value)
				free(old_env->value);
			old_env->value = ft_strdup(new_value);
		}
	}
	else if (ft_strcmp(key, "_"))
	{
		old_env = ft_env_new(key);
		if (!old_env)
			return (1);
		if (value)
			old_env->value = ft_strdup(new_value);
		ft_env_add_back(&ms->envp, old_env);
	}
	if (new_value)
		free(new_value);
	return (0);
}

void	print_tab_sort(char *tab)
{
	int	i;

	i = 0;
	printf("declare -x ");
	while (tab[i] && tab[i] != '=')
	{
		printf("%c", tab[i]);
		i++;
	}
	if (tab[i])
		printf("%c", tab[i++]);
	else
	{
		printf("\n");
		return ;
	}
	printf("%c", '"');
	while (tab[i])
	{
		printf("%c", tab[i]);
		i++;
	}
	printf("%c%c", '"', '\n');
}

char	**bubble_sort(char **tab)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (tab[i])
	{
		j = i + 1;
		while (tab[j])
		{
			if (ft_strcmp(tab[i], tab[j]) > 0)
			{
				temp = tab[i];
				tab[i] = tab[j];
				tab[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (tab);
}

void	print_export_values(t_minishell *ms)
{
	char	**tab;
	int		i;

	tab = list_to_tab(ms->envp);
	if (!tab)
		return ;
	tab = bubble_sort(tab);
	i = 0;
	while (tab[i])
	{
		print_tab_sort(tab[i]);
		i++;
	}
	free_all(tab);
}

int	process_export_arg(t_minishell *ms, char *arg)
{
	char	*equal;
	char	*key;
	char	*value;
	int		ret;

	equal = ft_strchr(arg, '=');
	if (!equal)
	{
		key = ft_strdup(arg);
		value = NULL;
	}
	else
	{
		*equal = '\0';
		key = ft_strdup(arg);
		value = ft_strdup(equal + 1);
		*equal = '=';
	}
	if (!key || (equal && !value))
		return (free(key), free(value), 1);
	ret = add_or_update_env(ms, key, value);
	free(key);
	if (value)
		free(value);
	return (ret);
}

int	ms_export(t_minishell *ms, t_cmd *cmd)
{
	int		i;
	char	*clean_arg;
	int		ret;
	char	*expanded;

	ret = 0;
	if (ft_tablen(cmd->args) == 1)
	{
		print_export_values(ms);
		return (0);
	}
	i = 1;
	while (cmd->args[i])
	{
		expanded = ft_expand_arg(ms, cmd->args[i]);
		clean_arg = ft_remove_quotes(expanded);
		if (expanded)
			free(expanded);
		if (!clean_arg)
			return (1);
		if (!is_valid_export_key(clean_arg))
		{
			ft_putstr_fd("Minishell: export: `", 2);
			ft_putstr_fd(cmd->args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			ret = 1;
		}
		else
		{
			if (process_export_arg(ms, clean_arg))
				ret = 1;
		}
		free(clean_arg);
		i++;
	}
	ms->status = ret;
	return (ret);
}
