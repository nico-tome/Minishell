/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 13:55:12 by ntome             #+#    #+#             */
/*   Updated: 2025/12/17 01:47:22 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <minishell.h>

int	is_quoted(char *word)
{
	if (!word)
		return (0);
	if (word[0] == '"' || word[0] == '\'')
		return (1);
	return (0);
}

int	print_env_var(t_minishell *ms, char *word, int *i)
{
	char	*env_name;
	char	*env_value;
	int		start;

	*i += 1;
	start = *i;
	while (word[*i] && (ft_isalnum(word[*i]) || word[*i] == '_'))
		*i += 1;
	env_name = ft_substr(word, start, *i - start);
	if (!env_name[0])
		printf("$");
	else if (!ft_strncmp(env_name, "?", ft_strlen(env_name)))
		printf("%d", ms->status);
	else if (!ft_strncmp(env_name, "$", ft_strlen(env_name)))
		printf("$");
	else
	{
		env_value = get_env(ms->envp, env_name);
		if (!env_value)
			return (0);
		printf("%s", env_value);
	}
	free(env_name);
	return (1);
}

int	print_echo(t_minishell *ms, char *word, int quoted)
{
	int		i;
	int		size;
	char	first_quote;
	int		len;

	size = ft_strlen(word);
	i = quoted;
	len = 0;
	if (quoted)
		first_quote = word[0];
	else
		first_quote = '\0';
	while (i < size && word[i] && word[i] != first_quote)
	{
		if (word[i] == '$' && first_quote != '\'')
			len += print_env_var(ms, word, &i);
		else
		{
			len++;
			printf("%c", word[i]);
			i++;
		}
	}
	return (len);
}

void	ms_echo(t_minishell *ms, t_cmd *cmd)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	while (cmd->args[i])
	{
		if (i == 1 && !ft_strcmp(cmd->args[i], "-n"))
		{
			new_line = 0;
			i++;
		}
		else
		{
			if (print_echo(ms, cmd->args[i], is_quoted(cmd->args[i])) &&
				cmd->args[i + 1] && !is_quoted(cmd->args[i + 1]))
				printf(" ");
			i++;
		}
	}
	if (new_line)
		printf("\n");
}
