/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 23:13:22 by ntome             #+#    #+#             */
/*   Updated: 2026/01/08 19:37:21 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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

	result_path = ft_strjoin("\033[32m~", pwd + ft_strlen(home));
	if (!result_path)
		return (NULL);
	result_prompt = ft_strjoin(result_path, " \033[0m| 🐚: ");
	free(result_path);
	return (result_prompt);
}

char	*create_exit_str(t_minishell ms)
{
	char	*exit_str;
	char	*colored_prompt;
	char	*tmp;

	exit_str = ft_itoa(ms.status);
	if (!exit_str)
		return (NULL);
	tmp = ft_strjoin(exit_str, ") \033[0m");
	free(exit_str);
	if (!tmp)
		return (NULL);
	if (ms.status != 0)
		colored_prompt = ft_strjoin("\033[31m(", tmp);
	else
		colored_prompt = ft_strjoin("\033[92m(", tmp);
	free(tmp);
	return (colored_prompt);
}

char	*ms_get_prompt(t_minishell ms)
{
	char	*prompt;
	char	*tmp;
	char	*exit_status;
	char	*home;

	exit_status = create_exit_str(ms);
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
