/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:42:06 by ntome             #+#    #+#             */
/*   Updated: 2025/12/11 16:32:43 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define C1 "\033[38;5;129m"
#define C2 "\033[38;5;171m"
#define C3 "\033[38;5;210m"
#define C4 "\033[38;5;45m"
#define RESET "\033[0m"

int	g_exit_status = 0;

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
	ms->envp = init_env(envp);
	ms->exit_status = 0;
	ms->pwd = getcwd(NULL, 0);
	ms->prompt_params = ms_init_prompt_params();
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	ms;
	char		*prompt;
	char		*cmd;
	t_token		*tokens;
	t_cmd		*parsed_cmd;

	(void)ac;
	(void)av;
	ms_print_hello();
	ms_init_data(&ms, envp);
	while (1)
	{
		prompt = ms_get_prompt(ms);
		cmd = readline(prompt);
		free(prompt);
		if (cmd[0] != '\0')
		{
			add_history(cmd);
			tokens = ft_calloc(1, sizeof(t_token));
			if (!tokens)
			{
				free(cmd);
				break ;
			}
			ms_tokenize_cmd(&tokens, cmd);
			if (tokens && tokens->content) 
			{
				parsed_cmd = parser(tokens, ms.envp);
				if (parsed_cmd)
				{
					exec_line(parsed_cmd, ms.envp); 
					free_cmd_list(parsed_cmd);
				}
			}
			//free_token_list(tokens);
		}
		free(cmd);
	}
	free_env_list(ms.envp);
	rl_clear_history();
	return (ms.exit_status);
}