/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gajanvie.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:27:15 by gajanvie          #+#    #+#             */
/*   Updated: 2025/12/17 13:37:17 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_shoot2(void)
{
	printf("       ██▒▒▒▒▓█                              \n");
	printf("       ██▒▓█▒█▒                              \n");
	printf("       ▒░▒████░                              \n");
	printf("       ░▒▒████                               \n");
	printf("        ▒▒▒▒▒▒                               \n");
	printf("        █░░░▒▒▒                              \n");
	printf("█████▒  █▒▒▒▒▒▒██████████████████████████████\n");
	printf("█████████▒▒▒▒▒▒██████████████████████████████\n");
	printf("█████████░░░░░▒██████████████████████████████\n");
	printf("█████████▒░░░▒███████████████████████████████\n");
	printf("███████████▒░ ░██████████████████████████████\n");
	printf("█████████░ █ ░███████████████████████████████\n");
	printf("█████████░░█ ░███████████████████████████████\n");
	printf("█████████░░██░░██████████████████████████████\n");
	printf("\n");
}

void	print_shoot(void)
{
	printf(C1"Never stop shooting\n\n");
	printf(RESET);
	printf("                                             \n");
	printf("             ░   ░                           \n");
	printf("           ░ ▓███░                           \n");
	printf("             █▒▒▒▓                           \n");
	printf("              ▒▒░                            \n");
	printf("                               ░░            \n");
	printf("                            ████████         \n");
	printf("         █    ██           ████▓█████        \n");
	printf("         ▓█   █            ▒▒▒░▒▓█▓▓██        \n");
	printf("         █   ██               ░░░▒▒▒░         \n");
	printf("        ██▒  ██                               \n");
	printf("       ██░░░▒██                              \n");
	printf("       ██░░░███                              \n");
	print_shoot2();
}

void	not_valid_gajanvie(char **cmd)
{
	ft_putstr_fd("petit coquillage: gajanvie: ", 2);
	ft_putstr_fd(cmd[1], 2);
	ft_putstr_fd(" is not a valid argument\n", 2);
}

int	gajanvie(char **cmd)
{
	int	ret;
	int	len;
	
	len = ft_tablen(cmd);
	ret = 0;
	if (len > 2)
	{
		ft_putstr_fd("petit coquillage: gajanvie: too much arguments\n", 2);
		return (1);
	}
	if (len == 1)
		ft_putstr_fd("\n try:\n\tgajanvie shoot\n\tgajanvie gamble\n\tgajanvie latina\n\n", 1);
	else if (!ft_strcmp(cmd[1], "shoot"))
		print_shoot();
	else if (!ft_strcmp(cmd[1], "gamble"))
		ret = gamble();
	else if (!ft_strcmp(cmd[1], "latina"))
		print_latina();
	else
	{
		not_valid_gajanvie(cmd);
		return (1);
	}
	return (ret);
}
