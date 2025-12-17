/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 00:13:56 by ntome             #+#    #+#             */
/*   Updated: 2025/12/17 15:18:42 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	is_numeric(char *str)
{
	int		i;
	char	*str_val;

	str_val = ft_lltoa(ft_atoll(str));
	if (ft_strncmp(str, str_val, ft_strlen(str)) && str[0] != '+')
	{
		free(str_val);
		return (0);
	}
	free(str_val);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i])
			&& !(i == 0 && (str[i] == '-' || str[i] == '+')))
			return (0);
		i++;
	}
	return (1);
}

void	exit_free(t_minishell *ms)
{
	if (ms->tokens)
		free_tokens(ms->tokens);
	if (ms->parsed_cmd)
		free_cmd_list(ms->parsed_cmd);
	if (ms->envp)
		free_env_list(ms->envp);
	if (ms->pwd)
		free(ms->pwd);
}

void	ms_exit(t_minishell *ms, int print, char **cmd)
{
	int	args_num;

	args_num = ft_tablen(cmd);
	if (args_num >= 2 && !is_numeric(cmd[1]))
	{
		ft_putstr_fd("petit coquillage: exit: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(" : numeric argument needed\n", 2);
		ms->status = 2;
		g_exit_status = 2;
		return ;
	}
	else if (args_num > 2)
	{
		ft_putstr_fd("petit coquillage: exit: too much arguments\n", 2);
		ms->status = 1;
	}
	else if (args_num == 2 && is_numeric(cmd[1]))
		ms->status = ft_atoll(cmd[1]);
	exit_free(ms);
	if (print)
		ft_putstr_fd("exit\n", 2);
	rl_clear_history();
	exit(ms->status % 256);
}
