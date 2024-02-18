/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 22:33:35 by brayan            #+#    #+#             */
/*   Updated: 2024/02/17 18:20:57 by brayan           ###   ########.fr       */
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
* PRE: -
* POST: Devuelve el nombre de la variable de entorno
*/
char	*get_name_var(const char *s, int c)
{
	int		len;
	char	*var_name;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	var_name = NULL;
	while (len >= 0)
	{
		if (*(s + len) == (char)c)
		{
			var_name = ft_substr(s, 0, len);
			if (!var_name)
				return (NULL);
			break ;
		}
		len--;
	}
	return (var_name);
}
