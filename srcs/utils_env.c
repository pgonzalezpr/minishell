/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 22:26:59 by brayan            #+#    #+#             */
/*   Updated: 2024/02/12 23:53:31 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
* PRE: -
* POST: Devuelve la longitud de la variable
*/
int	get_len_variable(char *variable)
{
	int	len;

	len = 0;
	while (variable[len] && variable[len] != EQUAL)
		len++;
	return (len);
}

/*
* PRE: minishell != NULL
* POST: Devuelve true si las variables son iguales, false en caso contrario.
*/
int	are_equal_variables(char *variable_1, char *variable_2)
{
	int	len_1;
	int	len_2;

	len_1 = get_len_variable(variable_1);
	len_2 = get_len_variable(variable_2);
	if (len_1 >= len_2 && strncmp(variable_1, variable_2, len_2) == 0) 
	{
		if (len_1 == len_2 || variable_1[len_2] == EQUAL)
			return (1);
	}
	return (0);
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

/*
* PRE: env != NULL && searched_var != NULL
* POST: Devolvera la pos donde se encuentra la searched_var
*       dentro de las variables de env, en caso de no encontrarla
*       devolvera POS_NOT_FOUNDED
*/
int	get_pos_var_env(char **env, char *searched_var)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (are_equal_variables(env[i], searched_var))
			return (i);
	}
    return (POS_NOT_FOUNDED);
}