/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 23:13:22 by ntome             #+#    #+#             */
/*   Updated: 2025/12/12 21:35:14 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_prompt_params	ms_init_prompt_params(void)
{
	t_prompt_params	params;

	params.exit_status = 1;
	params.pwd = 1;
	return (params);
}

char	*add_abs_path(char *pwd, char *home)
{
	char	*result_path;
	char	*result_prompt;

	result_path = ft_strjoin("~", pwd + ft_strlen(home));
	if (!result_path)
		return (NULL);
	result_prompt = ft_strjoin(result_path, " | 🐚: ");
	free(result_path);
	return (result_prompt);
}

char	*create_exit_str(void)
{
	char	*tmp;
	char	*result;
	char	*exit_status;

	exit_status = ft_itoa(g_exit_status);
	result = ft_strjoin(exit_status, ") ");
	tmp = result;
	result = ft_strjoin("(", result);
	free(tmp);
	free(exit_status);
	return (result);
}

char	*ms_get_prompt(t_minishell ms)
{
	char	*prompt;
	char	*tmp;
	char	*exit_status;
	char	*home;

	exit_status = create_exit_str();
	if (ms.prompt_params.pwd)
	{
		home = get_env(ms.envp, "HOME");
		if (home && !ft_strncmp(ms.pwd, home, ft_strlen(home)))
			prompt = add_abs_path(ms.pwd, home);
		else
			prompt = ft_strjoin(ms.pwd, " | 🐚: ");
	}
	else
		prompt = ft_strjoin("", "🐚: ");
	if (ms.prompt_params.exit_status)
	{
		tmp = prompt;
		prompt = ft_strjoin(exit_status, prompt);
		free(tmp);
	}
	free(exit_status);
	return (prompt);
}
