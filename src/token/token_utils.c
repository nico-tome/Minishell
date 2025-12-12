/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 21:05:51 by ntome             #+#    #+#             */
/*   Updated: 2025/12/12 21:43:24 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_get_word_quote(char *cmd, int *i, int *start)
{
	char	current_quote;

	*start = *i;
	current_quote = cmd[*i];
	while (cmd[*i] && cmd[*i] != current_quote)
		*i += 1;
	*i += 1;
}

void	ms_get_word_redir(char *cmd, int *i, int *start)
{
	char	current_quote;

	*start = *i;
	current_quote = cmd[*i];
	while (cmd[*i] && cmd[*i] == current_quote)
		*i += 1;
}

void	ms_get_word(char *cmd, int *i, int *start)
{
	*start = *i;
	while (cmd[*i] && !is_quote_redir(cmd[*i]) && cmd[*i] != ' ')
		*i += 1;
}
