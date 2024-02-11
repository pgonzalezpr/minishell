/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 22:33:35 by brayan            #+#    #+#             */
/*   Updated: 2024/02/11 23:30:54 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
* PRE: cmd_line != NULL
* POST: Devuelve el total de comandos ingresados.
*/
int	get_total_commands(char *cmd_line)
{
	int	total;
	int	in_command;
	int	i;

	i = -1;
	total = 0;
	in_command = 0;
	while (cmd_line[++i])
	{
		if (cmd_line[i] != EMPTY && !in_command)
		{
			total++;
			in_command = 1;
		}
		else if (cmd_line[i] == EMPTY && in_command)
			in_command = 0;
	}
	return (total);
}
