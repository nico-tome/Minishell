/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 14:32:55 by gajanvie          #+#    #+#             */
/*   Updated: 2025/12/21 18:27:31 by ntome            ###   ########.fr       */
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

void	update_res(t_minishell *ms, char **res, char *str, int *i)
{
	char	*name;
	char	*tmp_val;

	*i += 1;
	name = get_var_name(str, i);
	tmp_val = get_var_value(ms, name);
	safe_append(res, tmp_val);
	free(name);
	free(tmp_val);
}

char	*ft_expand_arg(t_minishell *ms, char *str)
{
	char			*res;
	char			c[2];
	t_double_index	vec2;

	vec2.i = 0;
	vec2.j = 0;
	res = ft_strdup("");
	c[1] = '\0';
	while (str[vec2.i])
	{
		if (str[vec2.i] == '\'' && vec2.j != 2)
			vec2.j = vec2.j == 0;
		else if (str[vec2.i] == '"' && vec2.j != 1)
			vec2.j = 2 * (vec2.j == 0);
		if (str[vec2.i] == '$' && vec2.j != 1 && (ft_isalnum(str[vec2.i + 1])
				|| str[vec2.i + 1] == '_' || str[vec2.i + 1] == '?'))
			update_res(ms, &res, str, &vec2.i);
		else
		{
			c[0] = str[vec2.i++];
			safe_append(&res, c);
		}
	}
	return (res);
}
