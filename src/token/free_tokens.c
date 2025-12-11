/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:08:43 by ntome             #+#    #+#             */
/*   Updated: 2025/12/11 17:12:14 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_tokens(t_token *token)
{
	t_token	*next;

	while (token->type != END)
	{
		next = token->next;
		if (token->content)
			free(token->content);
		if (token)
			free(token);
		token = next;
	}
	if (token->content)
		free(token->content);
	if (token)
		free(token);
}
