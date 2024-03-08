/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:30:57 by brayan            #+#    #+#             */
/*   Updated: 2024/03/07 03:44:29 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: var != NULL
* POST: Devuelve true si la variable cumple el formato
*		key=value || key= || key====value 
*/
static int	check_var_format(char *var)
{
	char	*key;
	char	*value;

	if (!var)
		return (0);
	key = ft_substr(var, 0, get_len_key_var(var));
	if (!key)
		return (0);
	if (!is_valid_key_format(key))
		return (free(key), INVALID_KEY);
	free(key);
	value = ft_strchr(var, EQUAL);
	if (!value || (value && *value != EQUAL))
		return (0);
	return (1);
}

/*
* PRE: -
* POST: Gestiona el caso en el que la variable no existe, redimensionando
*		el env existente para agregar la nueva variable, liberando el viejo env.
*/
static char	**case_var_not_exist(char **env, char *new_var, int len_env)
{
	char	**new_env;
	int		status;

	status = get_cpy_env(&new_env, env, len_env + 1, IGNORE);
	if (status == ERROR)
		return (NULL);
	new_env[len_env + 1] = NULL;
	new_env[len_env] = ft_strdup(new_var);
	if (!new_env[len_env])
		return (NULL);
	return (new_env);
}

/*
* PRE: -
* POST: Gestiona el caso en el que la variable existe, liberando
*		la pos del env en la que esta la var vieja, y agregando
*		en esa posicion la new var, sin reedimensionar el env.
*/
static char	**case_var_exist(char **env, char *new_var,
	int pos_var_env, int len_env)
{
	char	**new_env;
	int		status;

	status = get_cpy_env(&new_env, env, len_env, IGNORE);
	if (status == ERROR)
		return (NULL);
	free(new_env[pos_var_env]);
	new_env[pos_var_env] = ft_strdup(new_var);
	if (!new_env[pos_var_env])
		return (NULL);
	return (new_env);
}

/*
* PRE: env != NULL cmd != NULL
* POST: Si el node_env no existe lo agrega al env, en caso de que
*		exista sobreescribe el value.
*/
static int	overwrite_env(t_minishell *minishell, char *new_var,
	int pos_var_env)
{
	int		len_env;
	char	**old_env;
	char	**new_env;

	len_env = get_len_env(minishell->envp);
	old_env = minishell->envp;
	if (pos_var_env != POS_NOT_FOUNDED)
		new_env = case_var_exist(old_env, new_var, pos_var_env, len_env);
	else
		new_env = case_var_not_exist(old_env, new_var, len_env);
	if (!new_env)
		return (ERROR);
	free_env(old_env, len_env);
	minishell->envp = new_env;
	return (SUCCESS);
}

/*
* PRE: minishell != NULL && cmd != NULL
* POST: Ejecuta el builtin export de la minishell.
*		Devolviendo el status de la operacion.
*/
int	builtin_export(t_minishell *minishell, char **cmd)
{
	int		pos_var_env;
	char	*key_var_cmd;

	if (!cmd[1])
		return (print_env(minishell->envp, MODE_EXPORT), SUCCESS);
	cmd++;
	while (*cmd)
	{
		if (check_var_format(*cmd) == INVALID_KEY)
		{
			printf("minishell: export: `%s': not a valid identifier\n", *cmd);
			break ;
		}
		key_var_cmd = ft_substr(*cmd, 0, get_len_key_var(*cmd));
		if (!key_var_cmd)
			return (ERROR);
		pos_var_env = get_pos_var_env(minishell->envp, key_var_cmd);
		if (overwrite_env(minishell, *cmd, pos_var_env) != SUCCESS)
			return (free(key_var_cmd), ERROR);
		free(key_var_cmd);
		cmd++;
	}
	return (SUCCESS);
}
