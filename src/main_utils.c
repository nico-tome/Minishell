/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 10:10:06 by ntome             #+#    #+#             */
/*   Updated: 2026/01/09 10:16:43 by ntome            ###   ########.fr       */
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
