/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:23:26 by ntome             #+#    #+#             */
/*   Updated: 2025/12/21 17:36:28 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	*clean_token(t_minishell *ms, char *token, int check_quote)
{
	t_clean_token_infos	cti;
	char				*tmp;

	cti.i = 0;
	cti.clean_token = NULL;
	while (token[cti.i])
	{
		if (need_to_continue(check_quote, token, &cti.i))
			continue ;
		else
			cti.part = get_part(ms, token, &cti.i, check_quote);
		if (!cti.clean_token && cti.part)
			cti.clean_token = ft_strdup(cti.part);
		else if (cti.part)
		{
			tmp = cti.clean_token;
			cti.clean_token = ft_strjoin(cti.clean_token, cti.part);
			free(tmp);
		}
		if (cti.part)
			free(cti.part);
	}
	if (token)
		free(token);
	return (cti.clean_token);
}

void	create_token(t_token *token, char *word, t_token_infos t_i, char *cmd)
{
	char	*chunk;

	chunk = ft_substr(cmd, t_i.start, t_i.i - t_i.start);
	token->next = NULL;
	token->content = NULL;
	token->type = EMPTY;
	if (word)
		token->content = ft_strdup(word);
	if (word && check_forbiden_char(word, chunk))
		token->type = TOKEN_ERROR;
	else if (word && !ft_strcmp("|", word) && !ft_strcmp("|", chunk))
		token->type = PIPE;
	else if (word && !ft_strcmp("<", word) && !ft_strcmp("<", chunk))
		token->type = REDIR_IN;
	else if (word && !ft_strcmp(">", word) && !ft_strcmp(">", chunk))
		token->type = REDIR_OUT;
	else if (word && !ft_strcmp("<<", word) && !ft_strcmp("<<", chunk))
		token->type = HEREDOC;
	else if (word && !ft_strcmp(">>", word) && !ft_strcmp(">>", chunk))
		token->type = APPEND;
	else if (check_token_error(word, chunk))
		token->type = TOKEN_ERROR;
	else
		token->type = WORD;
	free(chunk);
}

void	skip_spaces(char *cmd, int *i)
{
	while (cmd[*i] && cmd[*i] == ' ')
		*i += 1;
}

void	get_next_chunk(char *cmd, int *i)
{
	char	quoted;

	quoted = 0;
	if (is_quote_redir(cmd[*i]) == 2)
	{
		while (cmd[*i] && is_quote_redir(cmd[*i]) == 2)
			*i += 1;
	}
	else
	{
		while (cmd[*i] && !(cmd[*i] == ' ' && !quoted)
			&& !(is_quote_redir(cmd[*i]) == 2 && !quoted))
		{
			if (is_quote_redir(cmd[*i]) == 1 && !quoted)
				quoted = cmd[*i];
			else if (is_quote_redir(cmd[*i]) == 1 && quoted)
				quoted = 0;
			*i += 1;
		}
	}
}

void	ms_tokenize_cmd(t_minishell *ms, t_token **tokens, char *cmd)
{
	t_token			*actual_token;
	t_token_infos	t_infos;
	char			*token;

	actual_token = *tokens;
	t_infos.i = 0;
	while (cmd[t_infos.i])
	{
		skip_spaces(cmd, &t_infos.i);
		t_infos.start = t_infos.i;
		get_next_chunk(cmd, &t_infos.i);
		token = ft_substr(cmd, t_infos.start, t_infos.i - t_infos.start);
		token = clean_token(ms, token, 1);
		create_token(actual_token, token, t_infos, cmd);
		free(token);
		while (cmd[t_infos.i] && cmd[t_infos.i] == ' ')
			t_infos.i++;
		if (cmd[t_infos.i] && token)
		{
			actual_token->next = ft_calloc(1, sizeof(t_token));
			if (!actual_token->next)
				return ;
			actual_token = actual_token->next;
		}
	}
}
