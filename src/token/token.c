/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:23:26 by ntome             #+#    #+#             */
/*   Updated: 2026/01/08 18:42:24 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	*need_add_space(char *word, char *chunk, char *cmd, t_token_infos t_i)
{
	int	j;

	j = 0;
	if (ft_strcmp(word, " "))
		return (ft_strdup(word));
	if (chunk[0] == '"' && ft_strlen(chunk) == 3)
		return (ft_strdup(word));
	if (chunk[0] == '\'' && ft_strlen(chunk) == 3)
		return (ft_strdup(word));
	if (!ft_strcmp(chunk, "\"\"") || !ft_strcmp(chunk, "''"))
	{
		while (cmd[t_i.i + j])
		{
			if (cmd[t_i.i + j] > ' ')
				return (ft_strdup(""));
			j++;
		}
		return (ft_strdup(word));
	}
	return (ft_strdup(word));
}

void	create_token(t_token *token, char *word, t_token_infos t_i, char *cmd)
{
	char	*chunk;

	chunk = ft_substr(cmd, t_i.start, t_i.i - t_i.start);
	token->next = NULL;
	token->content = NULL;
	token->type = EMPTY;
	if (word)
		token->content = need_add_space(word, chunk, cmd, t_i);
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
	while (cmd[*i] && cmd[*i] >= 7 && cmd[*i] <= 32)
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
		while (cmd[*i] && !(cmd[*i] <= 32 && !quoted)
			&& !(is_quote_redir(cmd[*i]) == 2 && !quoted))
		{
			if (is_quote_redir(cmd[*i]) == 1 && !quoted)
				quoted = cmd[*i];
			else if (cmd[*i] == quoted)
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
	t_infos.check_quote = 0;
	while (cmd[t_infos.i])
	{
		skip_spaces(cmd, &t_infos.i);
		t_infos.start = t_infos.i;
		get_next_chunk(cmd, &t_infos.i);
		token = get_token(ms, cmd, t_infos);
		create_token(actual_token, token, t_infos, cmd);
		free(token);
		while (cmd[t_infos.i] && cmd[t_infos.i] == ' ')
			t_infos.i++;
		if (cmd[t_infos.i] && token)
		{
			t_infos.check_quote = actual_token->type == HEREDOC;
			actual_token->next = ft_calloc(1, sizeof(t_token));
			if (!actual_token->next)
				return ;
			actual_token = actual_token->next;
		}
	}
}
