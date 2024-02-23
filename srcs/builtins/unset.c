/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:40:02 by brayan            #+#    #+#             */
/*   Updated: 2024/02/23 01:45:37 by brayan           ###   ########.fr       */
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
	t_env	*tmp;

	while (*cmd)
	{
		if (is_valid_key_format(*cmd))
		{
			tmp = get_var_env(minishell->env, *cmd);
			if (tmp)
			{
				if (del_node_env(minishell->env, tmp) != SUCCESS)
					return (ERROR);
			}
		}
		cmd++;
	}
	return (SUCCESS);
}
