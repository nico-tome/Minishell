/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 15:06:33 by ntome             #+#    #+#             */
/*   Updated: 2025/12/16 17:50:05 by gajanvie         ###   ########.fr       */
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
	if (token && token->type == PIPE)
	{
		ft_putstr_fd("Minishell: syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	while (token)
	{
		if (token->type == PIPE)
		{
			if (!token->next || token->next->type == PIPE)
			{
				ft_putstr_fd("Minishell: syntax error near unexpected token `|'\n", 2);
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
			printf("`%s'\n",
				token->content);
			return (1);
		}
		else if (is_redirection(token) && token->next->type != WORD)
		{
			ft_putstr_fd("Minishell: syntax error near unexpected token `", 2);
			ft_putstr_fd(token->next->content, 2);
			ft_putstr_fd("'\n", 2);
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
