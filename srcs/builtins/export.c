/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:30:57 by brayan            #+#    #+#             */
/*   Updated: 2024/02/18 00:21:07 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: minishell != NULL && cmd != NULL
* POST: Devuelve la longitud el env nuevo incluyendo las variables nuevas.
*/
static int	get_len_env_without_repeats(t_minishell *minishell, char **cmd)
{
	char	*var_name_env;
	char	*var_name_cmd;
	int		len_new_env;
	int		i;
	int		j;

	len_new_env = get_len_matrix(minishell->env) + get_len_matrix(cmd);
	i = 0;
	while (cmd[++i])
	{
		j = -1;
		var_name_cmd = get_name_var(cmd[i], EQUAL);
		if (!var_name_cmd)
			len_new_env--;
		while (minishell->env[++j])
		{
			var_name_env = get_name_var(minishell->env[j], EQUAL);
			if (var_name_env && are_equal_variables(var_name_cmd, var_name_env))
			{
				len_new_env--;
				break ;
			}
		}
	}
	return (len_new_env);
}

/*
* PRE: var != NULL && cmd != NULL
* POST: Verifica si la var esta en el cmd, en caso de que este
* 		 lo que hace es devolver una variable con el mismo nombre
* 		 pero con el valor modificado, en otro caso de vuelve la
* 		 var pasa por parametro con el valor no modificado.
*/
static char	*get_old_var_modified(char **var, char **cmd)
{
	int		i;
	char	*name_var_env;
	char	*name_var_cmd;
	char	*new_var;

	i = 0;
	new_var = ft_strdup(*var);
	if (!new_var)
		return (NULL);
	name_var_env = get_name_var(*var, EQUAL);
	if (!name_var_env)
		name_var_env = *var;
	while (cmd[++i])
	{
		name_var_cmd = get_name_var(cmd[i], EQUAL);
		if (name_var_cmd
			&& are_equal_variables(name_var_cmd, name_var_env))
		{
			free(new_var);
			new_var = ft_strdup(cmd[i]);
			break ;
		}
	}
	return (new_var);
}

/*
* PRE: var != NULL && cmd != NULL
* POST: Devuelve true si la variable existe (si esta en el env),
*		false en caso contario.
*/
static int	variable_exists(char *var, char **env)
{
	int		i;
	char	*name_var;
	char	*name_env;

	i = 0;
	name_var = get_name_var(var, EQUAL);
	if (!name_var)
		return (0);
	while (env[i])
	{
		name_env = get_name_var(env[i], EQUAL);
		if (name_env && are_equal_variables(name_var, name_env))
			return (1);
		i++;
	}
	return (0);
}

/*
* PRE: var != NULL && cmd != NULL
* POST: Genera un nuevo env con las nuevas variables recibidas del cmd.
*/
char	**get_new_env_with_new_vars(t_minishell *minishell, char **cmd,
	char **new_env)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (minishell->env[++i])
	{
		new_env[j] = get_old_var_modified(&minishell->env[i], cmd);
		if (!new_env[j])
			return (NULL);
		j++;
	}
	new_env[j] = NULL;
	i = 0;
	while (cmd[++i])
	{
		if (!variable_exists(cmd[i], new_env) && get_name_var(cmd[i], EQUAL))
		{
			new_env[j] = ft_strdup(cmd[i]);
			if (!new_env[j])
				return (NULL);
			j++;
		}
	}
	return (new_env);
}

/*
* PRE: minishell != NULL && cmd != NULL
* POST: Ejecuta el builtin export de la minishell.
*/
void	builtin_export(t_minishell *minishell, char **cmd)
{
	int		len_env;
	char	**new_env;

	if (!cmd[1])
		print_env(minishell->env, MODE_EXPORT);
	else
	{
		len_env = get_len_env_without_repeats(minishell, cmd);
		new_env = (char **)malloc((len_env + 1) * sizeof(char *));
		if (!new_env)
		{
			perror(RED ERROR_MALLOC DEF_COLOR);
			exit(EXIT_FAILURE);
		}
		new_env = get_new_env_with_new_vars(minishell, cmd, new_env);
		if (!new_env)
		{
			perror(RED ERROR_MALLOC DEF_COLOR);
			exit(EXIT_FAILURE);
		}
		free_matrix(minishell->env, get_len_matrix(minishell->env));
		new_env[len_env] = NULL;
		minishell->env = new_env;
	}
}
