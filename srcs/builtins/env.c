/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:32:06 by brayan            #+#    #+#             */
/*   Updated: 2024/02/20 04:17:39 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: minishell != NULL
* POST: Hara las acciones correspondientes del builtin env de la minishell
*/
int	builtin_env(t_minishell *minishell)
{
	if (get_total_commands(minishell->cmd_line) == 1)
		print_env(minishell->env, MODE_ENV);
	else
	{
		fprintf(stderr, RED MSG_MORE_THAN_TWO_ARGS_ENV DEF_COLOR);
		return (ERROR);
	}
	return (SUCCESS);
}
