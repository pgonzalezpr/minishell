/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 00:52:30 by brayan            #+#    #+#             */
/*   Updated: 2024/02/11 23:10:05 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: -
* POST: Imprimira un caracter por consola.
*/
static void	print_case(char c)
{
	if (c != DOUBLE_QUOTE && c != SINGLE_QUOTE)
		printf("%c", c);
}

/*
* PRE: CMD != NULL
* POST: Mostrara un mensaje por el standar output.
*/
int	echo_cmd(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	if (!cmd[1])
	{
		printf("%c", LINE_BREAK);
		return (SUCCESS);
	}
	else if (ft_strncmp(cmd[1], FLAG_N, 2) == 0)
		i = 1;
	while (cmd[++i])
	{
		j = -1;
		while (cmd[i][++j])
			print_case(cmd[i][j]);
		if (cmd[i + 1])
			printf("%c", EMPTY);
	}
	if (ft_strncmp(cmd[1], FLAG_N, 2) != 0)
		printf("%c", LINE_BREAK);
	return (SUCCESS);
}
