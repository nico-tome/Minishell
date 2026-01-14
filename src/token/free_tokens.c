/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:08:43 by ntome             #+#    #+#             */
/*   Updated: 2026/01/14 19:43:43 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	if (!token)
		return ;
	while (token)
	{
		tmp = token->next;
		if (token->content)
			free(token->content);
		free(token);
		token = tmp;
	}
}

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

void	free_tokens_parts(char ***tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
}
