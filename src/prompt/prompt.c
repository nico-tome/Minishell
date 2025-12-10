/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 23:13:22 by ntome             #+#    #+#             */
/*   Updated: 2025/12/10 20:05:39 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_prompt_params	ms_init_prompt_params(void)
{
	t_prompt_params	params;

	params.exit_status = 0;
	params.pwd = 0;
	return (params);
}

char	*ms_get_prompt(t_minishell ms)
{
	char	*prompt;
	char	*tmp;
	char	*exit_status;

	exit_status = ft_itoa(ms.exit_status);
	if (ms.prompt_params.pwd)
		prompt = ft_strjoin(ms.pwd, " | 🐚: ");
	else
		prompt = ft_strjoin("", "🐚: ");
	if (ms.prompt_params.exit_status)
	{
		tmp = prompt;
		prompt = ft_strjoin(") ", prompt);
		free(tmp);
		tmp = prompt;
		prompt = ft_strjoin(exit_status, prompt);
		free(tmp);
		tmp = prompt;
		prompt = ft_strjoin("(", prompt);
		free(tmp);
	}
	free(exit_status);
	return (prompt);
}
