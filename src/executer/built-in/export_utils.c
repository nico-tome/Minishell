/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 14:16:41 by gajanvie          #+#    #+#             */
/*   Updated: 2025/12/19 16:24:10 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_remove_quotes(char *str)
{
	char	*new;
	int		i;
	int		j;
	char	quote;

	if (!str)
		return (NULL);
	new = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && !quote)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		else
			new[j++] = str[i];
		i++;
	}
	return (new);
}

int	print_export_error(char *arg)
{
	ft_putstr_fd("Minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}
