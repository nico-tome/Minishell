/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_rand_name.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 16:18:38 by gajanvie          #+#    #+#             */
/*   Updated: 2025/12/17 13:20:28 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	make_printable(char *c)
{
	*c = ((unsigned char)*c % 94) + 33;
}

void	convert_alphabetical(unsigned int index, char *c)
{
	(void)index;
	*c = ((unsigned char)*c % 26) + 'a';
}

char	*ft_rand_name(void)
{
	char	*rand_name;
	int		fd;

	rand_name = malloc((sizeof(char) * 32) + 1);
	if (!rand_name)
		return (NULL);
	rand_name[32] = '\0';
	rand_name[0] = '/';
	rand_name[1] = 't';
	rand_name[2] = 'm';
	rand_name[3] = 'p';
	rand_name[4] = '/';
	fd = open ("/dev/urandom", O_RDONLY);
	if (fd < 0)
	{
		free(rand_name);
		return (NULL);
	}
	read(fd, rand_name + 5, 27);
	close (fd);
	ft_striteri(rand_name + 5, convert_alphabetical, 27);
	return (rand_name);
}
