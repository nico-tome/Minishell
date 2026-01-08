/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titan <titan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:09:43 by gajanvie          #+#    #+#             */
/*   Updated: 2026/01/08 21:54:37 by titan            ###   ########.fr       */
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
		if (g_exit_status == 130)
			break ;
		line = readline("> ");
		if (!line)
			break ;
		expand_line = ft_expand_arg(ms, line);
		if (delimiter[0] == '"' || delimiter[0] == '\'')
		{
			free(expand_line);
			expand_line = ft_strdup(line);
		}
		free(line);
		if (!expand_line)
			break ;
		if (ft_strcmp(expand_line, delimiter) == 0)
		{
			free(expand_line);
			break ;
		}
		write(fd_out, expand_line, ft_strlen(expand_line));
		write(fd_out, "\n", 1);
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

int	token_heredoc(t_token **tokens, t_cmd **curr_cmd, t_minishell *ms)
{
	char	*delimiter;
	char	*rand_name;
	pid_t	pid;
	int		ret;

	safe_close((*curr_cmd)->fd_in);
	*tokens = (*tokens)->next;
	delimiter = ft_expand_arg(ms, (*tokens)->content);
	if (!delimiter)
		return (1);
	rand_name = ft_rand_name();
	if (!rand_name)
	{
		free(delimiter);
		return (1);
	}
	pid = fork();
	if (pid == 0)
		pid_zero(ms, rand_name, delimiter, curr_cmd);
	else
	{
		free (delimiter);
		ret = other_pid(curr_cmd, pid, rand_name);
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
		if (tokens->type == PIPE)
			token_pipe(&curr_cmd);
		else if (tokens->type == REDIR_IN)
			token_redir_in(&tokens, &curr_cmd);
		else if (tokens->type == REDIR_OUT)
			token_redir_out(&tokens, &curr_cmd);
		else if (tokens->type == APPEND)
			token_append(&tokens, &curr_cmd);
		else if (tokens->type == WORD && tokens->content)
			add_to_cmd(curr_cmd, tokens->content, env, 0);
		else if (tokens->type == HEREDOC)
		{
			if (token_heredoc(&tokens, &curr_cmd, ms) == 1)
			{
				free_cmd_list(cmd_list);
				ms->status = 130;
				g_exit_status = 130;
				return (NULL);
			}
		}
		tokens = tokens->next;
	}
	return (cmd_list);
}
