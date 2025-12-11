/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:09:43 by gajanvie          #+#    #+#             */
/*   Updated: 2025/12/11 16:25:24 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_cmd	*create_new_cmd(void)
{
	t_cmd   *cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->cmd_path = NULL;
	cmd->fd_in = -2;
	cmd->fd_out = -2;
	cmd->status = 0;
	cmd->next = NULL;
	return (cmd);
}

t_cmd   *parser(t_token *tokens, t_env *env)
{
	t_cmd   *cmd_list;
	t_cmd   *curr_cmd;
	
	cmd_list = create_new_cmd();
	curr_cmd = cmd_list;
	while (tokens)
	{
		if (tokens->type == PIPE)
		{
			curr_cmd->next = create_new_cmd();
			curr_cmd = curr_cmd->next;
		}
		else if (tokens->type == REDIR_IN)
		{
			tokens = tokens->next; 
			curr_cmd->fd_in = open(tokens->content, O_RDONLY);
			if (curr_cmd->fd_out == -1)
			{
				curr_cmd->status = 1;
				perror("file");
			}
		}
		else if (tokens->type == REDIR_OUT)
		{
			tokens = tokens->next;
			curr_cmd->fd_out = open(tokens->content, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (curr_cmd->fd_out == -1)
			{
				curr_cmd->status = 1;
				perror("file");
			}
		}
		else if (tokens->type == APPEND)
		{
			if (curr_cmd->fd_out > -1)
				close(curr_cmd->fd_out);
			curr_cmd->fd_out = open(tokens->next->content, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (curr_cmd->fd_out == -1)
			{
				curr_cmd->status = 1;
				perror("file");
			}
		}
		else if (tokens->type == WORD)
			add_to_cmd(curr_cmd, tokens->content, env);
		tokens = tokens->next;
	}
	return (cmd_list);
}
