/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:06:06 by brayan            #+#    #+#             */
/*   Updated: 2024/02/25 23:53:54 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: -
* POST: Verifica si la option 1 es igual o diferente a la option 2
*/
static int	equal_option(char *op_1, char *op_2)
{
	while (*op_1 && *op_2 && *op_1 == *op_2)
	{
		op_1++;
		op_2++;
	}
	return (*op_1 - *op_2);
}

/*
* PRE: -
* POST: Verifica que el cmd_line tenga un formato valido, es decir,
*		Si viene de la siguiente manera "command" 'command' command
*/
static int	is_valid_format(char *cmd_line, char *option_1,
								char *option_2, char *option_3)
{
	return (equal_option(cmd_line, option_1) == 0 \
			|| equal_option(cmd_line, option_2) == 0 \
			|| equal_option(cmd_line, option_3) == 0);
}

/*
* PRE: -
* POST: Ejecuta el exit builtin
*/
static void	exit_builtin(t_minishell *minishell)
{
	rl_clear_history();
	clear_history();
	exit_minishell(minishell, "exit\n", EXIT_SUCCESS);
}

/*
* PRE: minishell != NULL
* POST: Seleccionara el builtin correspondiente devolviendo el estado
*		de la operacion (EXIT_FAILURE O EXIT_SUCCESS)
*/
int	select_builtin(t_minishell *minishell)
{
	char	**cmd;
	int		status;

	cmd = ft_split(minishell->cmd_line, EMPTY);
	status = SUCCESS;
	if (!cmd)
		return (printf(RED ERROR_MALLOC DEF_COLOR), EXIT_FAILURE);
	if (is_valid_format(cmd[0], EXIT_CMD, EXIT_CMD_2, EXIT_CMD_3))
		exit_builtin(minishell);
	else if (is_valid_format(cmd[0], ECHO_CMD, ECHO_CMD_2, ECHO_CMD_3))
		status = builtin_echo(minishell->env, cmd);
	else if (is_valid_format(cmd[0], CD_CMD, CD_CMD_2, CD_CMD_3))
		status = builtin_cd(minishell, cmd);
	else if (is_valid_format(cmd[0], ENV_CMD, ENV_CMD_2, ENV_CMD_3))
		status = builtin_env(minishell);
	else if (is_valid_format(cmd[0], EXP_CMD, EXP_CMD_2, EXP_CMD_3))
		status = builtin_export(minishell, cmd);
	else if (is_valid_format(cmd[0], PWD_CMD, PWD_CMD_2, PWD_CMD_3))
		status = builtin_pwd();
	else if (is_valid_format(cmd[0], UNSET_CMD, UNSET_CMD_2, UNSET_CMD_3))
		status = builtin_unset(minishell, cmd);
	else
		printf("%s %s", cmd[0], MSG_COMMAND_NOT_FOUND);
	return (free_matrix(cmd, get_len_matrix(cmd)), status);
}
