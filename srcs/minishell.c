/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro-go <pedro-go@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:34:27 by pedro-go          #+#    #+#             */
/*   Updated: 2024/04/13 15:34:28 by pedro-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 05:20:27 by brayan            #+#    #+#             */
/*   Updated: 2024/03/29 18:02:37 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			g_exit_status;

static void	check_empty_cmd_line_case(t_minishell *minishell, char *prompt)
{
	if (!minishell->cmd_line)
	{
		if (isatty(STDIN_FILENO))
			write(2, "exit\n", 6);
		free(prompt);
		exit_minishell(minishell, NULL, EXIT_SUCCESS);
	}
	else
		free(prompt);
}

static int	run_minishell(t_minishell *minishell)
{
	char	*prompt;

	while (1)
	{
		exec_signals(MODE_INTERACTIVE);
		prompt = build_prompt(minishell);
		if (!prompt)
			exit_minishell(minishell, PROMPT_ERR_MSG, EXIT_FAILURE);
		minishell->cmd_line = readline(prompt);
		check_empty_cmd_line_case(minishell, prompt);
		add_history(minishell->cmd_line);
		if (tokenize_cmdline(minishell) == -1 || check_syntax(minishell) == -1
			|| process_tokens(minishell) == -1 || build_pipeline(minishell)
			== -1)
		{
			clean_minishell(minishell, NOT_CLEAN_ENV);
			minishell->last_exit_code = EXIT_ERROR;
			continue ;
		}
		exec_pipeline(minishell);
		clean_minishell(minishell, NOT_CLEAN_ENV);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;

	if (argc > 1)
		return (ft_putstr_fd(MSG_TOO_MANY_ARGS_MINI, 2), EXIT_FAILURE);
	(void)argv;
	ft_memset(&minishell, 0, sizeof(minishell));
	if (get_cpy_env(&minishell.envp, env, get_len_env(env), IGNORE) != SUCCESS)
		exit_minishell(&minishell, MSG_ERROR_CPY_ENV, EXIT_FAILURE);
	g_exit_status = 0;
	return (run_minishell(&minishell));
}
