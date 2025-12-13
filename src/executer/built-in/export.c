/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 23:38:09 by ntome             #+#    #+#             */
/*   Updated: 2025/12/13 23:49:07 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_export_cmd(t_cmd *cmd)
{
	//il faut check si on a NOM=VALEUR;
}

void	ms_export(t_minishell *ms, t_cmd *cmd)
{
	t_env	*new_env;

	if (check_export_cmd(cmd))
	{
		new_env = ft_env_new(cmd->args[1]);
		ft_env_add_back(&ms->envp, new_env);
		//il faut peut-etre check si la valeur existe deja pour l'update au lieu de l'ajouter.
		//Aussi il faut peut etre trié les variables par ordre alphabetique mais pas sur, la doc est pas trop claire la dessus.
	}
}
