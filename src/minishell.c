/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:42:06 by ntome             #+#    #+#             */
/*   Updated: 2025/12/10 16:50:50 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

#define C1 "\033[38;5;129m"
#define C2 "\033[38;5;171m"
#define C3 "\033[38;5;210m"
#define C4 "\033[38;5;45m"
#define RESET "\033[0m"

void	ms_print_hello(void)
{
	printf(C1"  /$$$$$$                                /$$ /$$ /$$\n");
	printf(" /$$__  $$                              |__/| $$| $$\n");
	printf(C2"| $$  \\__/  /$$$$$$   /$$$$$$  /$$   /$$ /$$| $$| $$");
	printf("  /$$$$$$   /$$$$$$   /$$$$$$ \n");
	printf("| $$       /$$__  $$ /$$__  $$| $$  | $$| $$| $$| $$");
	printf(" |____  $$ /$$__  $$ /$$__  $$\n");
	printf(C3"| $$      | $$  \\ $$| $$  \\ $$| $$  | $$| $$| $$| $$");
	printf("  /$$$$$$$| $$  \\ $$| $$$$$$$$\n");
	printf("| $$    $$| $$  | $$| $$  | $$| $$  | $$| $$| $$| $$");
	printf(" /$$__  $$| $$  | $$| $$_____/\n");
	printf(C4"|  $$$$$$/|  $$$$$$/|  $$$$$$$|  $$$$$$/| $$| $$| $$");
	printf("|  $$$$$$$|  $$$$$$$|  $$$$$$$\n");
	printf(" \\______/  \\______/  \\____  $$ \\______/ |__/|__/|__/");
	printf(" \\_______/ \\____  $$ \\_______/\n");
	printf("                          ");
	printf("| $$                                 /$$");
	printf("  \\ $$\n                          ");
	printf("| $$                            ");
	printf("    |  $$$$$$/\n                          ");
	printf("|__/                     ");
	printf("            \\______/ \n");
	printf(RESET);
}

void	ms_init_data(t_minishell *ms, char **envp)
{
	ms->envp = envp;
	ms->exit_status = 0;
	ms->pwd = getcwd(NULL, 0);
	ms->prompt_params = ms_init_prompt_params();
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	ms;
	char		*prompt;
	char		*cmd;

	(void)ac;
	(void)av;
	ms_print_hello();
	ms_init_data(&ms, envp);
	while (1)
	{
		prompt = ms_get_prompt(ms);
		cmd = readline(prompt);
		/* apres le parsing faut check ca soit on l'excute en bultin soit en pipeline mais mec cd /tmp | grep caca 
		ca va dans la pipeline alors que juste cd /tmp on le fait en bultin
		j'ai pas code is_builtin_parent c juste check si c pas un des bultin moi je travail sur exec_line
		if (cmd_list->next == NULL && is_builtin_parent(cmd_list->args[0]))
		{
  			exec_builtin(cmd_list, env_list);
		}
		else
		{
			exec_line(cmd_list, env_list);
		}*/
		if (strcmp("pwd", cmd) == 0)
		{
			printf("%s\n", ms.pwd);
		}
		else if (strcmp("exit", cmd) == 0)
		{
			exit(EXIT_SUCCESS);
		}
		free(cmd);
	}
}
