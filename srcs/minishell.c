/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 05:20:27 by brayan            #+#    #+#             */
/*   Updated: 2024/02/14 04:33:15 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_minishell(t_minishell *minishell, char *msg, int status)
{
	clean_minishell(minishell);
	if (msg)
		printf("%s\n", msg);
	exit(status);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	ft_memset(&minishell, 0, sizeof(minishell));
	if (init_env(env, &minishell) != SUCCESS)
		return (EXIT_FAILURE);
	while (1)
	{
		minishell.cmd_line = readline(GREEN "minishell$ " DEF_COLOR);
		if (!minishell.cmd_line)
			continue ;
		if (ft_strequals(minishell.cmd_line, "EXIT"))
			exit_minishell(&minishell, NULL, EXIT_SUCCESS);
		add_history(minishell.cmd_line);
		if (tokenize_cmd_line(&minishell) == -1 || process_tokens(&minishell)
			== -1 || build_pipeline(&minishell) == -1)
		{
			clean_minishell(&minishell);
			continue ;
		}
		exec_pipeline(&minishell);
		clean_minishell(&minishell);
	}
}
