/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 23:13:22 by ntome             #+#    #+#             */
/*   Updated: 2025/12/10 01:05:41 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_prompt_params	ms_init_prompt_params(void)
{
	t_prompt_params	params;

	params.exit_status = 0;
	params.pwd = 0;
	params.time = 0;
	return (params);
}

char	*ms_get_prompt(t_minishell ms)
{
	(void)ms;
	return ("🐚: ");
}
