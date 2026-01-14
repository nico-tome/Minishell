/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gajanvie.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:27:15 by gajanvie          #+#    #+#             */
/*   Updated: 2026/01/14 14:40:22 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_shoot2(int fd_out)
{
	ft_putstr_fd("       ██▒▒▒▒▓█                              \n", fd_out);
	ft_putstr_fd("       ██▒▓█▒█▒                              \n", fd_out);
	ft_putstr_fd("       ▒░▒████░                              \n", fd_out);
	ft_putstr_fd("       ░▒▒████                               \n", fd_out);
	ft_putstr_fd("        ▒▒▒▒▒▒                               \n", fd_out);
	ft_putstr_fd("        █░░░▒▒▒                              \n", fd_out);
	ft_putstr_fd("█████▒  █▒▒▒▒▒▒██████████████████████████████\n", fd_out);
	ft_putstr_fd("█████████▒▒▒▒▒▒██████████████████████████████\n", fd_out);
	ft_putstr_fd("█████████░░░░░▒██████████████████████████████\n", fd_out);
	ft_putstr_fd("█████████▒░░░▒███████████████████████████████\n", fd_out);
	ft_putstr_fd("███████████▒░ ░██████████████████████████████\n", fd_out);
	ft_putstr_fd("█████████░ █ ░███████████████████████████████\n", fd_out);
	ft_putstr_fd("█████████░░█ ░███████████████████████████████\n", fd_out);
	ft_putstr_fd("█████████░░██░░██████████████████████████████\n", fd_out);
	ft_putstr_fd("\n", fd_out);
}

void	print_shoot(int fd_out)
{
	ft_putstr_fd(C1"Never stop shooting\n\n", fd_out);
	ft_putstr_fd(RESET, fd_out);
	ft_putstr_fd("                                             \n", fd_out);
	ft_putstr_fd("             ░   ░                           \n", fd_out);
	ft_putstr_fd("           ░ ▓███░                           \n", fd_out);
	ft_putstr_fd("             █▒▒▒▓                           \n", fd_out);
	ft_putstr_fd("              ▒▒░                            \n", fd_out);
	ft_putstr_fd("                               ░░            \n", fd_out);
	ft_putstr_fd("                            ████████         \n", fd_out);
	ft_putstr_fd("         █    ██           ████▓█████        \n", fd_out);
	ft_putstr_fd("         ▓█   █            ▒▒▒░▒▓█▓▓██        \n", fd_out);
	ft_putstr_fd("         █   ██               ░░░▒▒▒░         \n", fd_out);
	ft_putstr_fd("        ██▒  ██                               \n", fd_out);
	ft_putstr_fd("       ██░░░▒██                              \n", fd_out);
	ft_putstr_fd("       ██░░░███                              \n", fd_out);
	print_shoot2(fd_out);
}

void	not_valid_gajanvie(char **cmd)
{
	ft_putstr_fd("petit coquillage: gajanvie: ", 2);
	ft_putstr_fd(cmd[1], 2);
	ft_putstr_fd(" is not a valid argument\n", 2);
}

void	print_gajanvie_error(int fd_out)
{
	ft_putstr_fd("\n try:\n\tgajanvie shoot", fd_out);
	ft_putstr_fd("\n\tgajanvie gamble\n\tgajanvie latina\n\n", fd_out);
}

int	gajanvie(char **cmd, int fd_out)
{
	int	ret;
	int	len;

	len = ft_tablen(cmd);
	ret = 0;
	g_exit_status = 0;
	if (len > 2)
		ft_putstr_fd("petit coquillage: gajanvie: too much arguments\n", 2);
	if (len > 2)
		return (1);
	if (len == 1)
		print_gajanvie_error(fd_out);
	else if (!ft_strcmp(cmd[1], "shoot"))
		print_shoot(fd_out);
	else if (!ft_strcmp(cmd[1], "gamble"))
		ret = gamble(fd_out, 0, 0);
	else if (!ft_strcmp(cmd[1], "latina"))
		print_latina(fd_out);
	else
	{
		not_valid_gajanvie(cmd);
		return (1);
	}
	signal(SIGINT, signal_handler);
	return (ret);
}
