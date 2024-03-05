/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:42:17 by brayan            #+#    #+#             */
/*   Updated: 2024/03/05 19:07:00 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: -
* POST: Ejecuta el exit builtin
*/
int	builtin_exit(t_minishell *minishell, char **args)
{
	rl_clear_history();
	clear_history();
	free_str_arr(args);
	exit_minishell(minishell, NULL, CLEAN_ENV);
	return (SUCCESS);
}
