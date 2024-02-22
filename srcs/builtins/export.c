/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:30:57 by brayan            #+#    #+#             */
/*   Updated: 2024/02/22 16:37:56 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: minishell != NULL && cmd != NULL
* POST: Ejecuta el builtin export de la minishell.
*		Devolviendo el status de la operacion.
*/
int	builtin_export(t_minishell *minishell, char **cmd)
{
	int	status;
	int	i;

	i = 0;
	if (!cmd[1])
		print_env(minishell->env, MODE_EXPORT);
	else
	{
		while (cmd[++i])
		{
			if (is_valid_var_format(cmd[i]))
			{
				if (get_var_env(cmd[i]))
				{
					// modifico su valor.
				}
				else
				{
					// la agrego como nueva.
				}
			}
		}
		get
		set_node_content();
	}
	return (SUCCESS);
}
