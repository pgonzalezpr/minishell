/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:42:17 by brayan            #+#    #+#             */
/*   Updated: 2024/03/29 18:46:25 by brayan           ###   ########.fr       */
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

/*
* PRE: -
* POST: Ejecuta el proceso de salida.
*/
static void	exec_exit(t_minishell *minishell, char **args, int exit, int err)
{
	if (exit == 255 && err)
	{
		ft_putstr_fd(EXIT_CMD, STDERR_FILENO);
		ft_putchar_fd(LINE_BREAK, STDERR_FILENO);
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd(EXIT_CMD, 1);
		ft_putchar_fd(LINE_BREAK, 1);
	}
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
		exec_exit(minishell, args, EXIT_SUCCESS, 0);
	else if (args[2])
	{
		ft_putstr_fd(EXIT_CMD, STDERR_FILENO);
		ft_putchar_fd(LINE_BREAK, STDERR_FILENO);
		ft_putstr_fd(MSG_TOO_MANY_ARGS_EXIT, STDERR_FILENO);
	}
	else if (!is_numeric_exit_status(args[1]))
		exec_exit(minishell, args, 255, 1);
	else
		exec_exit(minishell, args, ft_atoi(args[1]), 0);
	return (SUCCESS);
}
