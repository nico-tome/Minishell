/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gamble.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 12:14:06 by gajanvie          #+#    #+#             */
/*   Updated: 2025/12/18 15:13:52 by gajanvie         ###   ########.fr       */
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

void	print_slot(char casino[3], char real_casino[3], int i)
{
	write(1, "|", 1);
	if (i < 300)
		write(1, &casino[0], 1);
	else
		write(1, &real_casino[0], 1);
	write(1, "| |", 3);
	if (i < 600)
		write(1, &casino[1], 1);
	else
		write(1, &real_casino[1], 1);
	write(1, "| |", 3);
	if (i != 900)
		write(1, &casino[2], 1);
	else
		write(1, &real_casino[2], 1);
	write(1, "|", 1);
}

void	print_casino(char casino[3], int end, char real_casino[3], int i)
{
	print_slot(casino, real_casino, i);
	ft_wait();
	write(1, "\r", 1);
	if (end)
	{
		write(1, "\n\n", 2);
		if (real_casino[0] == real_casino[1]
			&& real_casino[1] == real_casino[2])
			printf("Jackpot !!!!\n");
		else
			printf("Loser, (you are one click away from the jackpot...)\n");
	}
}

int	gamble(void)
{
	int		fd;
	int		i;
	char	casino[3];
	char	real_casino[3];

	i = 0;
	fd = open("/dev/urandom", O_RDONLY);
	if (fd < 0)
	{
		perror("open urandom ");
		return (1);
	}
	fill_casino(real_casino, fd);
	while (i < 900)
	{
		if (fill_casino(casino, fd))
		{
			perror("read fail ");
			return (1);
		}
		print_casino(casino, 0, real_casino, i++);
	}
	print_casino(casino, 1, real_casino, 900);
	safe_close(fd);
	return (0);
}
