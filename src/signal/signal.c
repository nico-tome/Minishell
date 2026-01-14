/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titan <titan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 23:48:50 by ntome             #+#    #+#             */
/*   Updated: 2026/01/14 09:36:47 by titan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	signal_handler(int signal)
{
	(void)signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 130;
}

void	signal_handler_gamble(int signal)
{
	(void)signal;
	printf("\n");
	g_exit_status = 130;
}
