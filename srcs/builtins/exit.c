/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:42:17 by brayan            #+#    #+#             */
/*   Updated: 2024/03/09 03:20:35 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: -
* POST: Chequea si la salida es un arg numerico
*/
static int	is_numeric_exit_status(char *args)
{
	if (!args)
		return (0);
	while (ft_isdigit((*args)) && (*args))
		args++;
	return (*args == NULL_STR);
}

static void	exec_exit(t_minishell *minishell, char **args, int exit)
{
	printf("%s\n", EXIT_CMD);
	if (exit == 255)
		printf("minishell: exit: %s: numeric argument required\n", args[1]);
	rl_clear_history();
	clear_history();
	free_str_arr(args);
	exit_minishell(minishell, NULL, exit);
}

/*
* PRE: -
* POST: Ejecuta el exit builtin
*/
int	builtin_exit(t_minishell *minishell, char **args)
{
	if (!args[1])
		exec_exit(minishell, args, EXIT_SUCCESS);
	else if (args[2])
		printf(MSG_TOO_MANY_ARGS_EXIT);
	else if (!is_numeric_exit_status(args[1]))
		exec_exit(minishell, args, 255);
	else
		exec_exit(minishell, args, ft_atoi(args[1]));
	return (SUCCESS);
}
