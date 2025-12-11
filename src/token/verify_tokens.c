/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 15:06:33 by ntome             #+#    #+#             */
/*   Updated: 2025/12/11 16:19:37 by ntome            ###   ########.fr       */
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

int	check_pipe(t_token *token)
{
	int	first;

	first = 1;
	while (token->type != END)
	{
		if (token->type == PIPE && first)
			return (1);
		else if (token->type == PIPE && token->next->type == END)
			return (1);
		first = 0;
		token = token->next;
	}
	return (0);
}

int	check_redirections(t_token *token)
{
	int	first;

	first = 1;
	while (token->type != END)
	{
		if (is_redirection(token) && first)
			return (1);
		else if (is_redirection(token) && token->next->type == END)
			return (1);
		first = 0;
		token = token->next;
	}
	return (0);
}
