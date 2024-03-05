/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:42:17 by brayan            #+#    #+#             */
/*   Updated: 2024/03/05 00:33:27 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: -
* POST: Ejecuta el exit builtin
*/
int	builtin_exit(t_minishell *minishell)
{
	rl_clear_history();
	clear_history();
	exit_minishell(minishell, NULL, CLEAN_ENV);
	return (SUCCESS);
}
