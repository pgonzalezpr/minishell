/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:40:02 by brayan            #+#    #+#             */
/*   Updated: 2024/03/04 00:39:58 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: var != NULL
* POST: Devuelve true si la variable cumple el formato
*		key
*/
static int	is_valid_key_format(char *var)
{
	if (!var)
		return (0);
	while (*var)
	{
		if (*var == EQUAL)
			return (0);
		var++;
	}
	return (1);
}

/*
* PRE: minishell != NULL
* POST: Elimina las variables de entorno recibidas de cmd
*		en el env de la minishell, devolviendo el status
*		de la operacion.
*/
int	builtin_unset(t_minishell *minishell, char **cmd)
{
	char	**new_env;
	int		pos_var_env;
	int		len_env;
	int		status;

	if (minishell->envp)
		len_env = get_len_env(minishell->envp);
	while (*cmd && minishell->envp)
	{
		if (is_valid_key_format(*cmd))
		{
			pos_var_env = get_pos_var_env(minishell->envp, *cmd);
			if (pos_var_env != POS_NOT_FOUNDED)
			{
				status = get_cpy_env(&new_env, minishell->envp, \
				--len_env, pos_var_env);
				if (status == ERROR)
					return (ERROR);
				free_env(minishell->envp, len_env + 1);
				minishell->envp = new_env;
			}
		}
		cmd++;
	}
	return (SUCCESS);
}
