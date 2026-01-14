/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titan <titan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 09:38:35 by ntome             #+#    #+#             */
/*   Updated: 2026/01/14 09:13:33 by titan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*clean_delimiter(char *delimiter)
{
	char	*clean_delimiter;
	char	quote;
	int		i;

	if (delimiter[0] != '"' && delimiter[0] != '\'')
		return (ft_strdup(delimiter));
	quote = delimiter[0];
	i = 1;
	while (delimiter[0] && delimiter[i] && delimiter[i] != quote)
		i++;
	clean_delimiter = ft_substr(delimiter, 1, i - 1);
	return (clean_delimiter);
}

int	stop_heredoc(char *line, char *delimiter)
{
	char	*expand_delimiter;

	expand_delimiter = clean_delimiter(delimiter);
	if (!ft_strcmp(line, expand_delimiter))
	{
		free(expand_delimiter);
		return (1);
	}
	free(expand_delimiter);
	return (0);
}

char	*find_expand_line(char *delimiter, t_minishell *ms, char *line)
{
	char	*expand_line;

	if (ms->expand_heredoc == 1)
	{
		expand_line = ft_expand_arg(ms, line);
		if (delimiter[0] == '"' || delimiter[0] == '\'')
		{
			free(expand_line);
			expand_line = ft_strdup(line);
		}
		return (expand_line);
	}
	else
	{
		expand_line = ft_strdup(line);
		if (delimiter[0] == '"' || delimiter[0] == '\'')
		{
			free(expand_line);
			expand_line = ft_strdup(line);
		}
		return (expand_line);
	}
}

int	handle_token_heredoc(t_token *tokens, t_minishell *ms,
	t_cmd *curr_cmd, t_cmd *cmd_list)
{
	if (token_heredoc(&tokens, &curr_cmd, ms, cmd_list) == 1)
	{
		free_cmd_list(cmd_list);
		free_cmd_list(curr_cmd);
		ms->status = 130;
		g_exit_status = 130;
		return (1);
	}
	return (0);
}

char	*process_heredoc_delimiter(char *raw, t_minishell *ms)
{
	char	*clean;
	int		i;
	int		j;
	char	quote;

	clean = ft_calloc(ft_strlen(raw) + 1, sizeof(char));
	if (!clean)
		return (NULL);
	ms->expand_heredoc = 1;
	i = 0;
	j = 0;
	quote = 0;
	while (raw[i])
	{
		if ((raw[i] == '\'' || raw[i] == '"') && quote == 0)
		{
			quote = raw[i];
			ms->expand_heredoc = 0;
		}
		else if (raw[i] == quote)
			quote = 0;
		else
		{
			clean[j] = raw[i];
			j++;
		}
		i++;
	}
	return (clean);
}
