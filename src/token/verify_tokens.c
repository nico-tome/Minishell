/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 15:06:33 by ntome             #+#    #+#             */
/*   Updated: 2025/12/12 10:36:35 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_redirection(t_token *token)
{
	if (token->type == REDIR_IN)
		return (1);
	else if (token->type == REDIR_OUT)
		return (1);
	else if (token->type == HEREDOC)
		return (1);
	else if (token->type == APPEND)
		return (1);
	else
		return (0);
}

int check_pipe(t_token *token)
{
	if (token && token->type == PIPE)
	{
		printf("Minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	while (token)
	{
		if (token->type == PIPE)
		{
			if (!token->next || token->next->type == PIPE)
			{
				printf("Minishell: syntax error near unexpected token `|'\n");
				return (1);
			}
		}
		token = token->next;
	}
	return (0);
}

int	check_redirections(t_token *token)
{
	while (token)
	{
		if (is_redirection(token) && !token->next)
		{
			printf("Minishell: syntax error near unexpected token `%s'\n", token->next->content);
			return (1);
		}
		else if (is_redirection(token) && token->next->type != WORD)
		{
			printf("Minishell: syntax error near unexpected token `%s'\n", token->next->content);
			return (1);
		}
		token = token->next;
	}
	return (0);
}

int	check_forbiden_char(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (word[i] == ';' || word[i] == '\\')
			return (1);
		i++;
	}
	return (0);
}
