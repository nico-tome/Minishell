/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:23:26 by ntome             #+#    #+#             */
/*   Updated: 2025/12/17 21:45:44 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

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

char	*clean_token(t_minishell *ms, char *token, int check_quote)
{
	char	*clean_token;
	int		i;
	char	*part;
	char	*tmp;

	i = 0;
	clean_token = NULL;
	while (token[i])
	{
		if (check_quote && (token[i] == '"' || token[i] == '\''))
			part = extract_quote(ms, token, &i);
		else if (token[i] == '$')
			part = extract_env(ms, token, &i);
		else
			part = extract_word(token, &i);
		if (!clean_token && part)
			clean_token = ft_strdup(part);
		else if (part)
		{
			tmp = clean_token;
			clean_token = ft_strjoin(clean_token, part);
			free(tmp);
		}
		if (part)
			free(part);
	}
	if (token)
		free(token);
	return (clean_token);
}

void	ms_create_token(t_token *token, char *word)
{
	token->next = NULL;
	token->content = NULL;
	if (word)
		token->content = ft_strdup(word);
	if (word && check_forbiden_char(word))
		token->type = TOKEN_ERROR;
	else if (word && ft_strncmp("|", word, ft_strlen(word)) == 0)
		token->type = PIPE;
	else if (word && ft_strncmp("<", word, ft_strlen(word)) == 0)
		token->type = REDIR_IN;
	else if (word && ft_strncmp(">", word, ft_strlen(word)) == 0)
		token->type = REDIR_OUT;
	else if (word && ft_strncmp("<<", word, ft_strlen(word)) == 0)
		token->type = HEREDOC;
	else if (word && ft_strncmp(">>", word, ft_strlen(word)) == 0)
		token->type = APPEND;
	else if (!word)
			token->type = EMPTY;
	else if (is_quote_redir(word[0]) == 2)
		token->type = TOKEN_ERROR;
	else
		token->type = WORD;
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
		while (cmd[*i] && !(cmd[*i] == ' ' && !quoted) && !(is_quote_redir(cmd[*i]) == 2 && !quoted))
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
	t_token	*actual_token;
	char	*token;
	int		i;
	int		start;

	actual_token = *tokens;
	i = 0;
	while (cmd[i])
	{
		skip_spaces(cmd, &i);
		start = i;
		get_next_chunk(cmd, &i);
		token = ft_substr(cmd, start, i - start);
		token = clean_token(ms, token, 1);
		ms_create_token(actual_token, token);
		free(token);
		if (cmd[i] == ' ' && token)
		{
			i++;
			actual_token->next = ft_calloc(1, sizeof(t_token));
			if (!actual_token->next)
				return ;
			actual_token = actual_token->next;
		}
	}
}
