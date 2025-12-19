/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntome <ntome@42angouleme.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 16:28:00 by ntome             #+#    #+#             */
/*   Updated: 2025/12/19 16:28:51 by ntome            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_tab_sort(char *tab)
{
	int	i;

	i = 0;
	printf("declare -x ");
	while (tab[i] && tab[i] != '=')
	{
		printf("%c", tab[i]);
		i++;
	}
	if (tab[i])
		printf("%c", tab[i++]);
	else
	{
		printf("\n");
		return ;
	}
	printf("%c", '"');
	while (tab[i])
	{
		printf("%c", tab[i]);
		i++;
	}
	printf("%c%c", '"', '\n');
}

char	**bubble_sort(char **tab)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (tab[i])
	{
		j = i + 1;
		while (tab[j])
		{
			if (ft_strcmp(tab[i], tab[j]) > 0)
			{
				temp = tab[i];
				tab[i] = tab[j];
				tab[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (tab);
}

void	print_export_values(t_minishell *ms)
{
	char	**tab;
	int		i;

	tab = list_to_tab(ms->envp);
	if (!tab)
		return ;
	tab = bubble_sort(tab);
	i = 0;
	while (tab[i])
	{
		print_tab_sort(tab[i]);
		i++;
	}
	free_all(tab);
}
