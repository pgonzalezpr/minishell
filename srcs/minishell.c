/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 05:20:27 by brayan            #+#    #+#             */
/*   Updated: 2024/03/03 16:50:54 by brayan           ###   ########.fr       */
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

int	check_syntax(t_minishell *minishell)
{
	t_list	*prev;
	t_list	*curr;

	prev = NULL;
	curr = minishell->tokens;
	while (curr)
	{
		if ((is_operator(curr->content) && (!curr->next
					|| is_operator(curr->next->content)))
			|| (ft_strequals(curr->content, PIPE) && !prev))
		{
			printf("%s", SYNTAX_ERR_MSG);
			return (-1);
		}
		prev = curr;
		curr = curr->next;
	}
	return (1);
}

static void	run_minishell(t_minishell *minishell)
{
	while (1)
	{
		minishell->cmd_line = readline(GREEN "minishell$ " DEF_COLOR);
		if (!minishell->cmd_line)
			continue ;
		if (ft_strequals(minishell->cmd_line, "EXIT"))
			exit_minishell(minishell, NULL, EXIT_SUCCESS);
		add_history(minishell->cmd_line);
		if (tokenize_cmdline(minishell) == -1 || check_syntax(minishell) == -1
			|| process_tokens(minishell) == -1 || build_pipeline(minishell)
			== -1)
		{
			clean_minishell(minishell);
			continue ;
		}
		//print_minishell(minishell);
		exec_pipeline(minishell);
		clean_minishell(minishell);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	ft_memset(&minishell, 0, sizeof(minishell));
	minishell.envp = env;
	if (init_env(&minishell, env) != SUCCESS)
		return (clean_minishell(&minishell), EXIT_FAILURE);
	run_minishell(&minishell);
}
