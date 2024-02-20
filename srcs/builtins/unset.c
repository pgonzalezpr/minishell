/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:40:02 by brayan            #+#    #+#             */
/*   Updated: 2024/02/20 04:29:35 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: minishell != NULL
* POST: Devuelve la longitud del nuevo env.
*/
static int	get_len_new_env(char **cmd, char **env)
{
	int	i;
	int	j;
	int	equals;
	int	len;

	i = -1;
	len = 0;
	while (env[++i])
	{
		j = 0;
		equals = 0;
		while (!equals && cmd[++j])
			equals = are_equal_variables(env[i], cmd[j]);
		if (!equals)
			len++;
	}
	return (len);
}

/*
* PRE: minishell != NULL
* POST: Genera un new env que contenga las variables de
*		entorno que no estan en el cmd, devolviendo
*		el status de la operacion.	
*/
int	get_new_env(t_minishell *minishell, char **cmd,
							char **new_env)
{
	int		i;
	int		j;
	int		w;
	int		equals;

	i = -1;
	w = -1;
	while (minishell->env[++i])
	{
		j = -1;
		equals = 0;
		while (!equals && cmd[++j])
			equals = are_equal_variables(minishell->env[i], cmd[j]);
		if (!equals)
		{
			new_env[++w] = ft_strdup(minishell->env[i]);
			if (!new_env[w])
			{
				perror(RED ERROR_MALLOC DEF_COLOR);
				free_matrix(new_env, w);
				return (ERROR);
			}
		}
	}
	return (SUCCESS);
}

/*
* PRE: minishell != NULL
* POST: Elimina las variables de entorno recibidas de cmd
*		en el env de la minishell, devolviendo el status
*		de la operacion.
*/
int	builtin_unset(t_minishell *minishell, char **cmd)
{
	char	**new_env;
	int		status;
	int		len_env;

	if (!cmd[1])
		return (EXIT_FAILURE);
	len_env = get_len_new_env(cmd, minishell->env);
	new_env = (char **)malloc((len_env + 1) * sizeof(char *));
	if (!new_env)
		return (perror(RED ERROR_MALLOC DEF_COLOR), ERROR);
	status = get_new_env(minishell, cmd, new_env);
	if (new_env)
	{
		free_matrix(minishell->env, get_len_matrix(minishell->env));
		new_env[len_env] = NULL;
		minishell->env = new_env;
	}
	return (status);
}
