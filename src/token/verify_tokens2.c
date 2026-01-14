/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_tokens2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: titan <titan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 09:08:35 by titan             #+#    #+#             */
/*   Updated: 2026/01/14 09:09:32 by titan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_unclosed_quotes(char *line)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (line[i])
	{
		if (quote == 0 && (line[i] == '\'' || line[i] == '"'))
			quote = line[i];
		else if (line[i] == quote)
			quote = 0;
		i++;
	}
	if (quote != 0)
	{
		ft_putstr_fd("Minishell: syntax error: unclosed quotes\n", 2);
		return (1);
	}
	return (0);
}
