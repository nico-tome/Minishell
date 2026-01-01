/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 21:37:01 by ntome             #+#    #+#             */
/*   Updated: 2026/01/01 22:17:15 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_pwd(t_minishell *ms)
{
	char	*path;

	path = get_env(ms->envp, "PWD");
	if (!path)
		path = getcwd(NULL, 0);
	if (path)
		printf("%s\n", path);
}
