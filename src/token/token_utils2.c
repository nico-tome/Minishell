/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 18:02:05 by ntome             #+#    #+#             */
/*   Updated: 2026/01/08 16:04:47 by ntome            ###   ########.fr       */
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

int	need_to_continue(int check_quote, char *token, int *i)
{
	if (check_quote && token[*i] == '$'
		&& (token[*i + 1] == '\'' || token[*i + 1] == '"'))
	{
		*i += 1;
		return (1);
	}
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

char	*get_part(t_minishell *ms, char *token, int *i, int check_quote)
{
	if (check_quote && (token[*i] == '"' || token[*i] == '\''))
		return (extract_quote(ms, token, i));
	else if (token[*i] == '$')
		return (extract_env(ms, token, i));
	return (extract_word(token, i, check_quote));
}

char	*get_token(t_minishell *ms, char *cmd, t_token_infos t_infos)
{
	char	*token;

	token = ft_substr(cmd, t_infos.start, t_infos.i - t_infos.start);
	token = clean_token(ms, token, !t_infos.check_quote);
	return (token);
}
