/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsaiago- <bsaiago-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:32:06 by brayan            #+#    #+#             */
/*   Updated: 2024/02/21 14:08:08 by bsaiago-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: minishell != NULL
* POST: Hara las acciones correspondientes del builtin env de la minishell
*/
int	builtin_env(t_minishell *minishell)
{
	if (get_len_env(minishell->env) == 1)
		print_env(minishell->env, MODE_ENV);
	else
	{
		fprintf(stderr, RED MSG_MORE_THAN_TWO_ARGS_ENV DEF_COLOR);
		return (ERROR);
	}
	return (SUCCESS);
}
