/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:09:43 by gajanvie          #+#    #+#             */
/*   Updated: 2025/12/17 15:02:29 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	token_pipe(t_cmd **curr_cmd)
{
	(*curr_cmd)->next = create_new_cmd();
	*curr_cmd = (*curr_cmd)->next;
}

void	run_heredoc(char *delimiter, int fd_out)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			if (line)
				free(line);
			break ;
		}
		write(fd_out, line, ft_strlen(line));
		write(fd_out, "\n", 1);
		free(line);
	}
}

void	token_heredoc(t_token **tokens, t_cmd **curr_cmd)
{
	int		tmp_fd;
	char	*delimiter;
	char	*rand_name;

	safe_close((*curr_cmd)->fd_in);
	*tokens = (*tokens)->next;
	delimiter = (*tokens)->content;
	rand_name = ft_rand_name();
	if (!rand_name)
	{
		(*curr_cmd)->status = 1;
		perror("heredoc temp file");
		return ;
	}
	tmp_fd = open(rand_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (tmp_fd == -1)
	{
		(*curr_cmd)->status = 1;
		perror("heredoc temp file");
		return ;
	}
	run_heredoc(delimiter, tmp_fd);
	close(tmp_fd);
	(*curr_cmd)->fd_in = open(rand_name, O_RDONLY);
	unlink(rand_name);
	free(rand_name);
	if ((*curr_cmd)->fd_in == -1)
	{
		(*curr_cmd)->status = 1;
		perror("heredoc open");
	}
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
		else if (tokens->type == HEREDOC)
			token_heredoc(&tokens, &curr_cmd);
		tokens = tokens->next;
	}
	return (cmd_list);
}
