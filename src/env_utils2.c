/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 22:48:58 by ntome             #+#    #+#             */
/*   Updated: 2025/12/14 22:49:52 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_env	*get_env_node(t_env *envp, char *env)
{
	while (envp)
	{
		if (!ft_strncmp(env, envp->key, ft_strlen(env)))
			return (envp);
		envp = envp->next;
	}
	return (NULL);
}
