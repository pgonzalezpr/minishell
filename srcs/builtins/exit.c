/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:42:17 by brayan            #+#    #+#             */
/*   Updated: 2024/03/07 00:46:22 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: -
* POST: Print exit message.
*/
static void	print_exit_message(char **args)
{
	int	i;

	if (!args || !*args)
		return ;
	args++;
	printf("%s\n", EXIT_CMD);
	while (*args)
	{
		i = 0;
		while (ft_isdigit((*args)[i]))
			i++;
		if ((*args)[i] != NULL_STR)
		{
			printf("minishell: exit: %s numeric argument required\n", *args);
			return ;
		}
		args++;
	}
}

/*
* PRE: -
* POST: Ejecuta el exit builtin
*/
int	builtin_exit(t_minishell *minishell, char **args)
{
	print_exit_message(args);
	rl_clear_history();
	clear_history();
	free_str_arr(args);
	exit_minishell(minishell, NULL, EXIT_SUCCESS);
	return (SUCCESS);
}
