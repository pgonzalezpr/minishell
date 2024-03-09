/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:40:02 by brayan            #+#    #+#             */
/*   Updated: 2024/03/09 04:59:34 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: minishell != NULL
* POST: Elimina las variables de entorno recibidas de cmd
*		en el env de la minishell, devolviendo el status
*		de la operacion.
*/
int	builtin_unset(t_minishell *minishell, char **cmd)
{
	char	**new_env;
	int		i;
	int		idx;
	int		len_env;
	int		status;

	if (minishell->envp)
		len_env = get_len_env(minishell->envp);
	while (cmd[++i] && minishell->envp)
	{
		idx = get_pos_var_env(minishell->envp, cmd[i]);
		if (idx != POS_NOT_FOUNDED)
		{
			status = get_cpy_env(&new_env, minishell->envp, --len_env, idx);
			if (status == ERROR)
				return (ERROR);
			free_env(minishell->envp, len_env + 1);
			minishell->envp = new_env;
		}
	}
	return (SUCCESS);
}
