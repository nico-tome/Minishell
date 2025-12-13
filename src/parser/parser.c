/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:09:43 by gajanvie          #+#    #+#             */
/*   Updated: 2025/12/13 16:59:22 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	token_pipe(t_cmd **curr_cmd)
{
	(*curr_cmd)->next = create_new_cmd();
	*curr_cmd = (*curr_cmd)->next;
}

void	token_redir_in(t_token **tokens, t_cmd **curr_cmd)
{
	if ((*curr_cmd)->fd_in > -1)
		close((*curr_cmd)->fd_in);
	(*tokens) = (*tokens)->next;
	(*curr_cmd)->fd_in = open((*tokens)->content, O_RDONLY);
	if ((*curr_cmd)->fd_in == -1)
	{
		(*curr_cmd)->status = 1;
		perror((*tokens)->content);
	}
}

void	token_redir_out(t_token **tokens, t_cmd **curr_cmd)
{
	if ((*curr_cmd)->fd_out > -1)
		close((*curr_cmd)->fd_out);
	(*tokens) = (*tokens)->next;
	(*curr_cmd)->fd_out = open((*tokens)->content,
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if ((*curr_cmd)->fd_out == -1)
	{
		(*curr_cmd)->status = 1;
		perror((*tokens)->content);
	}
}

void	token_append(t_token **tokens, t_cmd **curr_cmd)
{
	if ((*curr_cmd)->fd_out > -1)
		close((*curr_cmd)->fd_out);
	*tokens = (*tokens)->next;
	(*curr_cmd)->fd_out = open((*tokens)->content,
			O_CREAT | O_WRONLY | O_APPEND, 0644);
	if ((*curr_cmd)->fd_out == -1)
	{
		(*curr_cmd)->status = 1;
		perror("file");
	}
}

t_cmd	*parser(t_token *tokens, t_env *env)
{
	t_cmd	*cmd_list;
	t_cmd	*curr_cmd;

	cmd_list = create_new_cmd();
	curr_cmd = cmd_list;
	while (tokens)
	{
		if (tokens->type == PIPE)
			token_pipe(&curr_cmd);
		else if (tokens->type == REDIR_IN)
			token_redir_in(&tokens, &curr_cmd);
		else if (tokens->type == REDIR_OUT)
			token_redir_out(&tokens, &curr_cmd);
		else if (tokens->type == APPEND)
			token_append(&tokens, &curr_cmd);
		else if (tokens->type == WORD)
			add_to_cmd(curr_cmd, tokens->content, env);
		tokens = tokens->next;
	}
	return (cmd_list);
}
