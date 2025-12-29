/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 14:07:33 by gajanvie          #+#    #+#             */
/*   Updated: 2025/12/29 18:21:28 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	update_pwds(t_minishell *ms)
{
	char	*cwd;
	char	*old_pwd;

	old_pwd = get_env(ms->envp, "PWD");
	if (old_pwd)
		update_env_val(ms->envp, "OLDPWD", old_pwd);
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		update_env_val(ms->envp, "PWD", cwd);
		if (ms->pwd)
			free(ms->pwd);
		ms->pwd = ft_strdup(cwd);
		free(cwd);
	}
}

char	*expand_tilde(t_minishell *ms, char *path)
{
	char	*home;
	char	*new_path;

	home = get_env(ms->envp, "HOME");
	if (!home)
	{
		ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
		return (NULL);
	}
	if (!path || ft_strcmp(path, "~") == 0)
		return (ft_strdup(home));
	new_path = ft_strjoin(home, path + 1);
	return (new_path);
}

int	specific_cd(t_minishell *ms, char **path, int *print_path, t_cmd *cmd)
{
	if (!cmd->args[1])
	{
		*path = get_env(ms->envp, "HOME");
		if (!*path)
		{
			ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
			return (1);
		}
		return (0);
	}
	else if (ft_strcmp(cmd->args[1], "-") == 0)
	{
		*path = get_env(ms->envp, "OLDPWD");
		if (!*path)
		{
			ft_putstr_fd("Minishell: cd: OLDPWD not set\n", 2);
			return (1);
		}
		*print_path = 1;
		return (0);
	}
	return (2);
}

int	other_specific_cd(t_minishell *ms, char **path,
	int *should_free, t_cmd *cmd)
{
	if (cmd->args[1][0] == '~')
	{
		*path = expand_tilde(ms, cmd->args[1]);
		if (!*path)
			return (1);
		*should_free = 1;
	}
	else
		*path = cmd->args[1];
	return (0);
}

int	cd(t_minishell *ms, t_cmd *cmd)
{
	char	*path;
	int		print_path;
	int		should_free;
	int		ret;

	path = NULL;
	if (init_cd(&print_path, cmd, &should_free))
		return (1);
	ret = specific_cd(ms, &path, &print_path, cmd);
	if (ret == 1)
		return (1);
	if (ret == 2)
	{
		if (other_specific_cd(ms, &path, &should_free, cmd))
			return (1);
	}
	if (switch_dir(path, should_free, print_path))
		return (1);
	update_pwds(ms);
	if (should_free)
		free(path);
	return (0);
}
