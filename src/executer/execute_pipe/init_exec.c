/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 16:00:27 by gajanvie          #+#    #+#             */
/*   Updated: 2025/12/13 16:04:32 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	count_cmds(t_cmd *cmd)
{
	int	result;

	result = 0;
	while (cmd)
	{
		result++;
		cmd = cmd->next;
	}
	return (result);
}

char	**list_to_tab(t_env *env)
{
	char	**tab;
	int		size;
	int		i;
	t_env	*tmp;

	size = ft_env_size(env);
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp)
	{
		tab[i] = ft_join_value(tmp->key, tmp->value);
		if (!tab[i])
		{
			free_all(tab);
			return (NULL);
		}
		tmp = tmp->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

void	init_exec(t_exec *exec, t_minishell *ms)
{
	exec->cmd_list = ms->parsed_cmd;
	exec->env_list = ms->envp;
	exec->count = count_cmds(ms->parsed_cmd);
	exec->env_tab = list_to_tab(ms->envp);
	exec->pids = malloc(sizeof(pid_t) * exec->count);
	exec->ms = ms;
}
