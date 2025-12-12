/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 21:46:23 by ntome             #+#    #+#             */
/*   Updated: 2025/12/12 22:10:49 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ms_env(t_minishell *ms)
{
	t_env	*env;

	env = ms->envp;
	while (env->next)
	{
		printf("%s%s\n", env->key, env->value);
		env = env->next;
	}
}
