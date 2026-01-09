/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 09:38:35 by ntome             #+#    #+#             */
/*   Updated: 2026/01/09 10:03:20 by ntome            ###   ########.fr       */
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
