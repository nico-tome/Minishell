/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 13:55:12 by ntome             #+#    #+#             */
/*   Updated: 2025/12/16 15:33:02 by ntome            ###   ########.fr       */
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

void	print_env_var(t_minishell *ms, char *word, int *i)
{
	char	*env_name;
	char	*env_value;
	int		start;

	*i += 1;
	start = *i;
	while (word[*i] && (ft_isalnum(word[*i]) || word[*i] == '_'))
		*i += 1;
	env_name = ft_substr(word, start, *i - start);
	if (!env_name)
		return ;
	if (!ft_strncmp(env_name, "?", ft_strlen(env_name)))
		printf("%d", ms->status);
	else if (!ft_strncmp(env_name, "$", ft_strlen(env_name)))
		printf("$$");
	else
	{
		env_value = get_env(ms->envp, env_name);
		if (env_value)
			printf("%s", env_value);
	}
	free(env_name);
}

void	print_echo(t_minishell *ms, char *word, int quoted)
{
	int		i;
	int		size;
	char	first_quote;

	size = ft_strlen(word);
	i = quoted;
	if (quoted)
		first_quote = word[0];
	else
		first_quote = '\0';
	while (i < size && word[i] && word[i] != first_quote)
	{
		if (word[i] == '$' && first_quote != '\'')
			print_env_var(ms, word, &i);
		else
			printf("%c", word[i]);
		i++;
	}
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
			print_echo(ms, cmd->args[i], is_quoted(cmd->args[i]));
			i++;
			if (cmd->args[i] && !is_quoted(cmd->args[i]))
				printf(" ");
		}
	}
	if (new_line)
		printf("\n");
}
