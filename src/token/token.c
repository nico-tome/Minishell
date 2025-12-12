/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 20:23:26 by ntome             #+#    #+#             */
/*   Updated: 2025/12/12 10:29:13 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_has_error(t_token *token)
{
	if (check_pipe(token) || check_redirections(token))
		return (1);
	while (token)
	{
		if (token->type == TOKEN_ERROR)
			return (1);
		token = token->next;
	}
	return (0);
}

int	ms_check_quoted(char *word)
{
	char	current;

	current = 0;
	while (*word)
	{
		if (!current && (*word == '\'' || *word == '"'))
			current = *word;
		else if (current && *word == current)
			current = 0;
		word++;
	}
	return (current == 0);
}

char	*ms_get_next_word(char *cmd, int *i)
{
	int		start;
	char	*word;
	char	current_quote;

	word = NULL;
	current_quote = 0;
	*i += cmd[*i] == ' ';
	start = *i;
	while (cmd[*i])
	{
		if (cmd[*i] == '\'' || cmd[*i] == '"')
		{
			if (!current_quote)
				current_quote = cmd[*i];
			else if (cmd[*i] == current_quote)
				break ;
		}
		if (cmd[*i] == ' ' && !current_quote)
			break ;
		*i += 1;
	}
	if (start != *i)
		word = ft_substr(cmd, start, *i - start + (cmd[*i] == current_quote));
	*i += (cmd[*i] == current_quote && current_quote);
	return (word);
}

void	ms_create_token(t_token *token, char *word)
{
	token->next = NULL;
	token->content = ft_strdup(word);
	if (!ms_check_quoted(word) || check_forbiden_char(word))
		token->type = TOKEN_ERROR;
	else if (ft_strncmp("|", word, ft_strlen(word)) == 0)
		token->type = PIPE;
	else if (ft_strncmp("<", word, ft_strlen(word)) == 0)
		token->type = REDIR_IN;
	else if (ft_strncmp(">", word, ft_strlen(word)) == 0)
		token->type = REDIR_OUT;
	else if (ft_strncmp("<<", word, ft_strlen(word)) == 0)
		token->type = HEREDOC;
	else if (ft_strncmp(">>", word, ft_strlen(word)) == 0)
		token->type = APPEND;
	else
		token->type = WORD;
}

void	ms_tokenize_cmd(t_token **tokens, char *cmd)
{
	t_token	*actual_token;
	char	*word;
	int		i;

	actual_token = *tokens;
	i = 0;
	word = ms_get_next_word(cmd, &i);
	while (word)
	{
		ms_create_token(actual_token, word);
		free(word);
		word = ms_get_next_word(cmd, &i);
		if (word)
		{
			actual_token->next = ft_calloc(1, sizeof(t_token));
			if (!actual_token->next)
			{
				free(word);
				return ;
			}
			actual_token = actual_token->next;
		}
	}
}
