/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:09:43 by gajanvie          #+#    #+#             */
/*   Updated: 2026/01/15 12:36:55 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	token_pipe(t_cmd **curr_cmd)
{
	(*curr_cmd)->next = create_new_cmd();
	*curr_cmd = (*curr_cmd)->next;
}

void	run_heredoc(char *delimiter, int fd_out, t_minishell *ms)
{
	char	*line;
	char	*expand_line;

	while (1)
	{
		line = readline("> ");
		if (g_exit_status == 130)
		{
			if (line)
				free(line);
		}
		if (!line || g_exit_status == 130)
			break ;
		expand_line = find_expand_line(delimiter, ms, line);
		free(line);
		if (!expand_line)
			break ;
		if (stop_heredoc(expand_line, delimiter))
		{
			free(expand_line);
			break ;
		}
		write_heredoc(fd_out, expand_line);
		free(expand_line);
	}
}

void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_exit_status = 130;
	close (0);
}

int	token_heredoc(t_token **tokens, t_cmd **curr_cmd, t_minishell *ms,
	t_cmd *cmd_list)
{
	char	*delimiter;
	char	*rand_name;
	pid_t	pid;
	int		ret;

	safe_close((*curr_cmd)->fd_in);
	*tokens = (*tokens)->next;
	delimiter = process_heredoc_delimiter((*tokens)->content, ms, 0, 0);
	rand_name = heredoc_rand_check(delimiter);
	if (!rand_name)
		return (1);
	pid = fork();
	if (pid == -1)
		double_string_free(delimiter, rand_name);
	if (pid == -1)
		return (1);
	if (pid == 0)
		pid_zero(ms, rand_name, delimiter, cmd_list);
	else
	{
		free(delimiter);
		ret = other_pid(curr_cmd, pid, rand_name, ms);
		return (ret);
	}
	return (0);
}

t_cmd	*parser(t_token *tokens, t_env *env, t_minishell *ms)
{
	t_cmd	*cmd_list;
	t_cmd	*curr_cmd;

	cmd_list = create_new_cmd();
	curr_cmd = cmd_list;
	while (tokens)
	{
		if (tokens->type == PIPE
			|| tokens->type == REDIR_IN || tokens->type == REDIR_OUT)
			parser2(&tokens, &curr_cmd);
		else if (tokens->type == APPEND)
			token_append(&tokens, &curr_cmd);
		else if (tokens->type == WORD && tokens->content)
			add_to_cmd(curr_cmd, tokens->content, env, 0);
		else if (tokens->type == HEREDOC)
		{
			if (token_heredoc(&tokens, &curr_cmd, ms, cmd_list) == 1)
			{
				free_cmd_list(curr_cmd);
				return (NULL);
			}
		}
		tokens = tokens->next;
	}
	return (cmd_list);
}
