/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 18:02:05 by ntome             #+#    #+#             */
/*   Updated: 2025/12/19 18:02:32 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_quote_redir(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	else if (c == '>' || c == '<' || c == '|')
		return (2);
	return (0);
}

char	*join_token_part(char **token, char *part)
{
	char	*tmp;

	tmp = *token;
	*token = ft_strjoin(*token, part);
	free(tmp);
	return (*token);
}
