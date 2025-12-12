/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 14:07:33 by gajanvie          #+#    #+#             */
/*   Updated: 2025/12/12 17:21:38 by gajanvie         ###   ########.fr       */
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
	if (!path || ft_strncmp(path, "~", ft_strlen(path)) == 0)
		return (ft_strdup(home));
	new_path = ft_strjoin(home, path + 1);
	return (new_path);
}

int	cd(t_minishell *ms, t_cmd *cmd)
{
	char	*path;
	int		print_path;
	int		should_free;

	path = NULL;
	print_path = 0;
	should_free = 0;
	if (ft_tablen(cmd->args) > 2)
	{
		ft_putstr_fd("Minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (!cmd->args[1])
	{
		path = get_env(ms->envp, "HOME");
		if (!path)
		{
			ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
			return (1);
		}
	}
	else if (ft_strncmp(cmd->args[1], "-", ft_strlen(cmd->args[1])) == 0)
	{
		path = get_env(ms->envp, "OLDPWD");
		if (!path)
		{
			ft_putstr_fd("Minishell: cd: OLDPWD not set\n", 2);
			return (1);
		}
		print_path = 1;
	}
	else if (cmd->args[1][0] == '~')
	{
		path = expand_tilde(ms, cmd->args[1]);
		if (!path)
			return (1);
		should_free = 1;
	}
	else
		path = cmd->args[1];
	if (chdir(path) == -1)
	{
		ft_putstr_fd("Minishell: cd: ", 2);
		perror(path);
		if (should_free)
			free(path);
		return (1);
	}
	if (print_path)
		printf("%s\n", path);
	update_pwds(ms);
	if (should_free)
		free(path);
	return (0);
}
