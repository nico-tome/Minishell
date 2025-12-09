/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:42:06 by ntome             #+#    #+#             */
/*   Updated: 2025/12/09 22:02:04 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>
#include <string.h>

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	while (1)
	{
		char	*prompt = "🐚: ";
		char	*cmd = readline(prompt);
		if (strcmp("pwd", cmd) == 0)
		{
			char *path;
			path = getcwd(NULL, 0);
			printf("%s\n", path);
			free(path);
		}
		else if (strcmp("exit", cmd) == 0)
		{
			exit(EXIT_SUCCESS);
		}
		free(cmd);
	}
}
