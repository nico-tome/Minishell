/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gajanvie <gajanvie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:38:42 by gajanvie          #+#    #+#             */
/*   Updated: 2025/12/15 10:57:44 by gajanvie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	*old_shlvl;
	char	*new_shlvl;

	ms->envp = init_env(envp);
	ms->pwd = getcwd(NULL, 0);
	ms->tokens = NULL;
	ms->parsed_cmd = NULL;
	ms->status = 0;
	ms->prompt_params = ms_init_prompt_params();
	old_shlvl = get_env(ms->envp, "SHLVL");
	if (old_shlvl)
	{
		new_shlvl = ft_itoa(ft_atoi(old_shlvl) + 1);
		update_env_val(ms->envp, "SHLVL", new_shlvl);
		free(new_shlvl);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	ms;
	char		*prompt;
	char		*cmd;

	(void)ac;
	(void)av;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	ms_print_hello();
	ms_init_data(&ms, envp);
	while (1)
	{
		prompt = ms_get_prompt(ms);
		cmd = readline(prompt);
		free(prompt);
		if (cmd == NULL)
			ms_exit(&ms, 1, NULL);
		if (cmd[0] != '\0')
		{
			add_history(cmd);
			ms.tokens = ft_calloc(1, sizeof(t_token));
			if (!ms.tokens)
			{
				free(cmd);
				break ;
			}
			ms_tokenize_cmd(&ms.tokens, cmd);
			if (ms.tokens && ms.tokens->content && !ms_has_error(ms.tokens))
			{
				ms.parsed_cmd = parser(ms.tokens, ms.envp);
				if (ms.parsed_cmd)
				{
					if (ms.parsed_cmd->next == NULL
						&& is_builtin(ms.parsed_cmd->args[0]))
						exec_builtin(&ms, 1, ms.parsed_cmd, NULL);
					else
						exec_line(&ms);
					free_cmd_list(ms.parsed_cmd);
					ms.parsed_cmd = NULL;
				}
			}
			free_tokens(ms.tokens);
			ms.tokens = NULL;
		}
		free(cmd);
	}
	free_env_list(ms.envp);
	rl_clear_history();
	return (EXIT_SUCCESS);
}
