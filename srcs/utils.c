/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 22:33:35 by brayan            #+#    #+#             */
/*   Updated: 2024/03/03 22:42:50 by brayan           ###   ########.fr       */
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

/*
* PRE: -
* POST: Devuelve 0 si son iguales s1 y s2, negativo si s2 > s1 
*		y positivo en caso contrario.
*/
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
