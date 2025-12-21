/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titan <titan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 19:09:43 by gajanvie          #+#    #+#             */
/*   Updated: 2025/12/21 11:17:58 by titan            ###   ########.fr       */
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
		if (g_exit_status == 130)
			break ;
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd_out, line, ft_strlen(line));
		write(fd_out, "\n", 1);
		free(line);
	}
}

void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_exit_status = 130;
}

void	token_heredoc(t_token **tokens, t_cmd **curr_cmd, t_minishell *ms)
{
	int		tmp_fd;
	char	*delimiter;
	char	*rand_name;
	pid_t	pid;
	int		status;

	safe_close((*curr_cmd)->fd_in);
	*tokens = (*tokens)->next;
	delimiter = (*tokens)->content;
	rand_name = ft_rand_name();
	if (!rand_name)
		return ;
	pid = fork();
	if (pid == 0)
	{
		tmp_fd = open(rand_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (tmp_fd == -1)
		{
			perror("heredoc temp file");
			rl_clear_history();
			free_cmd_list(*curr_cmd);
			exit_free(ms);
			exit(1);
		}
		signal(SIGINT, heredoc_sigint_handler);
		run_heredoc(delimiter, tmp_fd);
		close(tmp_fd);
		free(rand_name);
		exit_free(ms);
		free_cmd_list(*curr_cmd);
		rl_clear_history();
		if (g_exit_status == 130)
			exit(130);
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			(*curr_cmd)->status = 130;
			unlink(rand_name);
			free(rand_name);
			return ;
		}
		signal(SIGINT, signal_handler);
		(*curr_cmd)->fd_in = open(rand_name, O_RDONLY);
		unlink(rand_name);
		free(rand_name);
		if ((*curr_cmd)->fd_in == -1)
		{
			(*curr_cmd)->status = 1;
			perror("heredoc open");
		}
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
			add_to_cmd(curr_cmd, tokens->content, env);
		else if (tokens->type == HEREDOC)
			token_heredoc(&tokens, &curr_cmd, ms);
		tokens = tokens->next;
	}
	return (cmd_list);
}
