/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 05:20:27 by brayan            #+#    #+#             */
/*   Updated: 2024/03/06 05:30:50 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_signal_status;

// Función de manejo de SIGINT (ctrl-C) SIGQUIT (ctrl-\) SIGTERM (ctrl-D)
void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		//printf("Ctrl + C handle\n");
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_signal_status = 1;
	}
	else if (signal == SIGQUIT)
	{
		//printf("Ctrl + D handle\n");
		rl_on_new_line();
		rl_redisplay();
		printf("  \b\b");
	}
}

static void	run_minishell(t_minishell *minishell)
{
	char	*prompt;

	while (1)
	{
		prompt = build_prompt(minishell);
		if (!prompt)
			exit_minishell(minishell, PROMPT_ERR_MSG, EXIT_FAILURE);
		if (!g_signal_status)
			minishell->cmd_line = readline(prompt);
		free(prompt);
		if (!minishell->cmd_line)
			continue ;
		add_history(minishell->cmd_line);
		if (tokenize_cmdline(minishell) == -1 || check_syntax(minishell) == -1
			|| process_tokens(minishell) == -1 || build_pipeline(minishell)
			== -1)
		{
			clean_minishell(minishell, NOT_CLEAN_ENV);
			continue ;
		}
		if (!g_signal_status)
			exec_pipeline(minishell);
		g_signal_status = 0;
		//print_minishell(minishell);
		clean_minishell(minishell, NOT_CLEAN_ENV);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;

	(void)argc;
	(void)argv;

	ft_memset(&minishell, 0, sizeof(minishell));
	minishell.cwd = getcwd(NULL, 0);
	if (!minishell.cwd)
		return (EXIT_FAILURE);
	if (get_cpy_env(&minishell.envp, env, get_len_env(env), IGNORE) != SUCCESS)
		exit_minishell(&minishell, MSG_ERROR_CPY_ENV, EXIT_FAILURE);
	/*
	if (protect_handle_signals_configure() == ERROR)
		exit_minishell(&minishell, MSG_ERROR_SIGNAL, EXIT_FAILURE);
	*/
	//signal(SIGINT, signal_handler);	
	run_minishell(&minishell);
}
