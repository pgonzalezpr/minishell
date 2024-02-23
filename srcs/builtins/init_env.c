/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 21:42:27 by brayan            #+#    #+#             */
/*   Updated: 2024/02/22 23:37:32 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: -
* POST: inicializa el env.
*/
int	init_env(t_minishell *minishell, char **env)
{
	t_env	*tmp;

	while (*env)
	{
		tmp = get_new_node_env(NULL, NULL);
		if (!tmp)
			return (ERROR);
		if (set_node_content(*env, &tmp) != SUCCESS)
			return (ERROR);
		add_back_to_env(&minishell->env, tmp);
		env++;
	}
	return (SUCCESS);
}
