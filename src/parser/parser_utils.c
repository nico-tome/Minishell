/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titan <titan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 17:38:39 by ntome             #+#    #+#             */
/*   Updated: 2026/01/08 21:42:41 by titan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

void	pid_zero(t_minishell *ms, char *r_name, char *del, t_cmd **curr_cmd)
{
	int		tmp_fd;

	tmp_fd = open(r_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (tmp_fd == -1)
	{
		perror("heredoc temp file");
		free(r_name);
		free(del);
		rl_clear_history();
		free_cmd_list(*curr_cmd);
		exit_free(ms);
		exit(1);
	}
	signal(SIGINT, heredoc_sigint_handler);
	run_heredoc(del, tmp_fd, ms);
	close(tmp_fd);
	free(r_name);
	free(del);
	exit_free(ms);
	free_cmd_list(*curr_cmd);
	rl_clear_history();
	if (g_exit_status == 130)
		exit(130);
	exit(0);
}

int	other_pid(t_cmd **curr_cmd, int pid, char *rand_name)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		|| (WIFEXITED(status) && WEXITSTATUS(status) == 130))
	{
		(*curr_cmd)->status = 130;
		unlink(rand_name);
		(*curr_cmd)->fd_in = -1;
		free(rand_name);
		return (1);
	}
	signal(SIGINT, signal_handler);
	(*curr_cmd)->fd_in = open(rand_name, O_RDONLY);
	unlink(rand_name);
	free(rand_name);
	if ((*curr_cmd)->fd_in == -1)
	{
		(*curr_cmd)->status = 1;
		perror("heredoc open");
		return (1);
	}
	return (0);
}
