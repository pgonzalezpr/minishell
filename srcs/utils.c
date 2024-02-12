/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 22:33:35 by brayan            #+#    #+#             */
/*   Updated: 2024/02/12 02:50:30 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
* PRE: -
* POST: Libera la memoria de la matrix.
*/
void	free_matrix(char **mat, int i)
{
	while (i-- > 0)
		free(mat[i]);
	free(mat);
}

/*
* PRE: -
* POST: Devuelve la longitud de la matrix
*/
int	get_len_matrix(char **matrix)
{
	int	size;

	size = 0;
	while (matrix[size])
		size++;
	return (size);
}

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
* PRE: minishell != NULL && matrix_ori != NULL
* POST: Genera una copia de la matrix original, devolviendo el estado
*       del proceso.
*/
int	get_cpy_env(t_minishell *minishell, char **matrix_ori)
{
	int	size;
	int	i;

	size = get_len_matrix(matrix_ori);
	minishell->env = (char **)malloc((size + 1) * sizeof(char *));
	if (!minishell->env)
	{
		perror(RED ERROR_MALLOC DEF_COLOR);
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < size)
	{
		minishell->env[i] = ft_strdup(matrix_ori[i]);
		if (!minishell->env[i])
		{
			perror(RED ERROR_MALLOC DEF_COLOR);
			free_matrix(minishell->env, i);
			exit(EXIT_FAILURE);
		}
	}
	minishell->env[size] = NULL;
	return (SUCCESS);
}
