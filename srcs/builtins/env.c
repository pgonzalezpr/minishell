/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:32:06 by brayan            #+#    #+#             */
/*   Updated: 2024/02/12 01:45:24 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: env != NULL
* POST: Imprime por consola las variables de entorno del minishell
*/
static void	print_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
}

/*
* PRE: minishell != NULL
* POST: -
*/
int	env_cmd(t_minishell *minishell)
{
	if (get_total_commands(minishell->cmd_line) == 1)
		print_env(minishell->env);
	else
	{
		// PENDING
	}
	return (SUCCESS);
}
