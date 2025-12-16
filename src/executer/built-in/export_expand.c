/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 14:32:55 by gajanvie          #+#    #+#             */
/*   Updated: 2025/12/16 14:44:25 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_var_value(t_minishell *ms, char *key)
{
	char	*val;
	char	*result;

	if (ft_strncmp(key, "?", 2) == 0)
	{
		result = ft_itoa(ms->status);
		return (result);
	}
	val = get_env(ms->envp, key);
	if (val)
	{
		result = ft_strdup(val);
		return (result);
	}
	result = ft_strdup("");
	return (result);
}

static char	*get_var_name(char *str, int *i)
{
	int		start;
	char	*result;

	start = *i;
	if (str[*i] == '?')
	{
		(*i)++;
		result = ft_strdup("?");
		return (result);
	}
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	result = ft_substr(str, start, *i - start);
	return (result);
}

void	safe_append(char **s1, char *s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = ft_strjoin(*s1, s2);
	free(tmp);
}

char	*ft_expand_arg(t_minishell *ms, char *str)
{
	char	*res;
	char	*tmp_val;
	char	*name;
	char	c[2];
	int		i;
	int		q;

	i = 0;
	q = 0;
	res = ft_strdup("");
	c[1] = '\0';
	while (str[i])
	{
		if (str[i] == '\'' && q != 2)
		{
			if (q == 0)
				q = 1;
			else
				q = 0;
		}
		else if (str[i] == '"' && q != 1)
		{
			if (q == 0)
				q = 2;
			else
				q = 0;
		}
		if (str[i] == '$' && q != 1 && (ft_isalnum(str[i + 1])
				|| str[i + 1] == '_' || str[i + 1] == '?'))
		{
			i++;
			name = get_var_name(str, &i);
			tmp_val = get_var_value(ms, name);
			safe_append(&res, tmp_val);
			free(name);
			free(tmp_val);
		}
		else
		{
			c[0] = str[i++];
			safe_append(&res, c);
		}
	}
	return (res);
}
