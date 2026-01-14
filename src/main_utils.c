/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 10:10:06 by ntome             #+#    #+#             */
/*   Updated: 2026/01/14 15:11:03 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_exit_status(t_minishell *ms, int check, int new_val, int check_r)
{
	if ((g_exit_status == check) == check_r)
		ms->status = new_val;
}

void	ft_void(int ac, char **av)
{
	(void)ac;
	(void)av;
}

void	write_heredoc(int fd_out, char *expand_line)
{
	write(fd_out, expand_line, ft_strlen(expand_line));
	write(fd_out, "\n", 1);
}

void	parser2(t_token *tokens, t_cmd	*curr_cmd)
{
	if (tokens->type == PIPE)
		token_pipe(&curr_cmd);
	else if (tokens->type == REDIR_IN)
		token_redir_in(&tokens, &curr_cmd);
	else if (tokens->type == REDIR_OUT)
		token_redir_out(&tokens, &curr_cmd);
}

char	*heredoc_rand_check(char *del)
{
	char	*rand;

	if (!del)
		return (NULL);
	rand = ft_rand_name();
	if (!rand)
		free(del);
	return (rand);
}
