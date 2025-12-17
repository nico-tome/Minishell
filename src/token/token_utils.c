/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 21:05:51 by ntome             #+#    #+#             */
/*   Updated: 2025/12/17 21:28:29 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <minishell.h>

char	*extract_env_name(char *token, int *i)
{
	char	*env_name;
	int		start;

	*i += 1;
	start = *i;
	while (token[*i] && token[*i] != '$' && token[*i] != '?')
	{
		if (!ft_isalnum(token[*i]) && token[*i] != '_')
			break;
		if (ft_isdigit(token[*i]) && *i - start == 0)
		{
			*i += 1;
			return (NULL);
		}
		*i += 1;
	}
	if ((token[*i] == '$' || token[*i] == '?') && *i == start)
		*i += 1;
	env_name = ft_substr(token, start, *i - start);
	return (env_name);
}

char	*extract_env(t_minishell *ms, char *token, int *i)
{
	char	*env_name;
	char	*env_value;
	char	*tmp;

	env_value = NULL;
	env_name = extract_env_name(token, i);
	if (env_name)
	{
		if (!ft_strcmp(env_name, "?"))
			env_value = ft_itoa(ms->status);
		else if (!ft_strcmp(env_name, "$") || !ft_strcmp(env_name, ""))
			env_value = ft_strdup("$");
		else
		{
			tmp = get_env(ms->envp, env_name);
			if (tmp)
				env_value = ft_strdup(tmp);
		}
		free(env_name);
	}
	return (env_value);
}

char	*extract_quote(t_minishell *ms, char *token, int *i)
{
	char	quote;
	char	*extracted;
	int		start;

	quote = token[*i];
	*i += 1;
	start = *i;
	while (token[*i] && token[*i] != quote)
		*i += 1;
	if (!token[*i])
		return (NULL);
	extracted = ft_substr(token, start, *i - start);
	*i += 1;
	if (quote == '"')
		extracted = clean_token(ms, extracted, 0);
	return (extracted);
}

char	*extract_word(char *token, int *i)
{
	int		start;
	char	*result;

	result = NULL;
	start = *i;
	while (token[*i] && token[*i] != '$'
		&& token[*i] != '"' && token[*i] != '\'')
		*i += 1;
	result = ft_substr(token, start, *i - start);
	return (result);
}
