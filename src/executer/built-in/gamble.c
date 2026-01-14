/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gamble.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 12:14:06 by gajanvie          #+#    #+#             */
/*   Updated: 2026/01/14 14:41:43 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	fill_casino(char casino[3], int fd)
{
	int		ret;
	char	buffer[4];

	ret = read(fd, buffer, 4);
	if (ret == -1)
		return (1);
	make_printable(&buffer[0]);
	make_printable(&buffer[1]);
	make_printable(&buffer[2]);
	if ((unsigned char)buffer[3] % 5 == 0)
	{
		buffer[1] = buffer[0];
		buffer[2] = buffer[0];
	}
	casino[0] = buffer[0];
	casino[1] = buffer[1];
	casino[2] = buffer[2];
	return (0);
}

void	ft_wait(void)
{
	int	i;
	int	limit;

	i = 0;
	limit = 1000000;
	while (i < limit)
		i++;
}

void	print_slot(char casino[3], char real_casino[3], int i, int fd_out)
{
	write(fd_out, "|", 1);
	if (i < 300)
		write(fd_out, &casino[0], 1);
	else
		write(fd_out, &real_casino[0], 1);
	write(fd_out, "| |", 3);
	if (i < 600)
		write(fd_out, &casino[1], 1);
	else
		write(fd_out, &real_casino[1], 1);
	write(fd_out, "| |", 3);
	if (i != 900)
		write(fd_out, &casino[2], 1);
	else
		write(fd_out, &real_casino[2], 1);
	write(fd_out, "|", 1);
}

void	print_casino(t_casino casino, int i, int fd_out)
{
	print_slot(casino.casino, casino.real_casino, i, fd_out);
	ft_wait();
	write(fd_out, "\r", 1);
	if (i == 900)
	{
		write(fd_out, "\n\n", 2);
		if (casino.real_casino[0] == casino.real_casino[1]
			&& casino.real_casino[1] == casino.real_casino[2])
			ft_putstr_fd("Jackpot !!!!\n", fd_out);
		else
		{
			ft_putstr_fd("Loser, (you are one ", fd_out);
			ft_putstr_fd("click away from the jackpot...)\n", fd_out);
		}
	}
}

int	gamble(int fd_out, int i, int fd)
{
	t_casino	casino;

	signal(SIGINT, signal_handler_gamble);
	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
		perror("open urandom ");
	if (fd < 0)
		return (1);
	fill_casino(casino.real_casino, fd);
	while (i <= 900)
	{
		if (g_exit_status == 130)
			safe_close(fd);
		if (g_exit_status == 130)
			return (130);
		if (fill_casino(casino.casino, fd))
		{
			perror("read fail ");
			safe_close(fd);
			return (1);
		}
		print_casino(casino, i++, fd_out);
	}
	safe_close(fd);
	return (0);
}
