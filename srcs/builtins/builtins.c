/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:06:06 by brayan            #+#    #+#             */
/*   Updated: 2024/02/14 04:02:51 by brayan           ###   ########.fr       */
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
* PRE: minishell != NULL
* POST: Seleccionara el comando.
*/
void	select_builtin(t_minishell *minishell)
{
	char	**cmd;

	cmd = ft_split(minishell->cmd_line, EMPTY);
	/*
	if (!cmd)
		// PROTEGER CMD.
	*/
	if (is_valid_format(cmd[0], EXIT_BUILTIN, EXIT_BUILTIN_2, EXIT_BUILTIN_3))
	{
		rl_clear_history();
		exit_minishell(minishell, NULL, EXIT_SUCCESS);
	}
	else if (is_valid_format(cmd[0], ECHO_BUILTIN, ECHO_BUILTIN_2,
			ECHO_BUILTIN_3))
		builtin_echo(cmd, minishell->env);
	else if (is_valid_format(cmd[0], CD_BUILTIN, CD_BUILTIN_2, CD_BUILTIN_3))
		builtin_cd(minishell, cmd);
	else if (is_valid_format(cmd[0], ENV_BUILTIN, ENV_BUILTIN_2, ENV_BUILTIN_3))
		builtin_env(minishell);
	else if (is_valid_format(cmd[0], EXP_BUILTIN, EXP_BUILTIN_2, EXP_BUILTIN_3))
		builtin_export(minishell);
	else if (is_valid_format(cmd[0], PWD_BUILTIN, PWD_BUILTIN, PWD_BUILTIN_3))
		builtin_pwd(&minishell->cwd);
	else if (is_valid_format(cmd[0], UNSET_BUILTIN, UNSET_BUILTIN_2,
			UNSET_BUILTIN_3))
		builtin_unset(minishell, cmd);
}
