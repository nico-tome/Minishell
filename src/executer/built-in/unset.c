/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titan <titan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 14:03:56 by titan             #+#    #+#             */
/*   Updated: 2025/12/13 14:38:28 by titan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	free_one_node(t_env *node)
{
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

void	remove_env_var(t_env **envp, char *key)
{
	t_env	*curr;
	t_env	*to_free;

	if (!*envp)
		return ;
	if (!ft_strcmp((*envp)->key, key))
	{
		to_free = *envp;
		*envp = (*envp)->next;
		free_one_node(to_free);
		return ;
	}
	curr = *envp;
	while (curr->next)
	{
		if (!ft_strcmp(curr->next->key, key))
		{
			to_free = curr->next;
			curr->next = to_free->next;
			free_one_node(to_free);
			return ;
		}
		curr = curr->next;
	}
}

int	ft_unset(t_minishell *ms, char **args)
{
	int	i;

	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		remove_env_var(&ms->envp, args[i]);
		i++;
	}
	return (0);
}
