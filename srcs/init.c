/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 21:42:27 by brayan            #+#    #+#             */
/*   Updated: 2024/02/11 22:53:48 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
* PRE: -
* POST: Libera la memoria de la matrix.
*/
static void	free_matrix(char **mat, int i)
{
	while (--i > 0)
		free(mat[i]);
	free(mat);
}

/*
* PRE: -
* POST: Devuelve la longitud del env
*/
static int	get_len_env(char **env)
{
	int	size;

	size = 0;
	while (env[size])
		size++;
	return (size);
}

/*
* PRE: -
* POST: Genera una copia del env.
*/
static int	get_cpy_env(char **env, t_minishell *minishell)
{
	int	size;
	int	i;

	size = get_len_env(env);
	minishell->env = (char **)malloc((size + 1) * sizeof(char *));
	if (!minishell->env)
	{
		perror("Error de asignación de memoria");
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < size)
	{
		minishell->env[i] = ft_strdup(env[i]);
		if (!minishell->env[i])
		{
			perror("Error de asignación de memoria");
			free_matrix(minishell->env, i);
			exit(EXIT_FAILURE);
		}
	}
	minishell->env[size] = NULL;
	return (SUCCESS);
}

/*
* PRE: -
* POST: inicializa el env.
*/
int	init_env(char **env, t_minishell *minishell)
{
	return (get_cpy_env(env, minishell));
}
