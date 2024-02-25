/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:30:57 by brayan            #+#    #+#             */
/*   Updated: 2024/02/25 23:25:30 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: var != NULL
* POST: Devuelve true si la variable cumple el formato
*		key=value || key=
*/
static int	is_valid_var_format(char *var)
{
	int	status;
	int	len_var;	
	int	count_equals;

	if (!var)
		return (0);
	len_var = ft_strlen(var);
	status = 1;
	if (len_var < 2)
		status = 0;
	if (var[0] == EQUAL)
		status = 0;
	count_equals = 0;
	while (*var && status)
	{
		if (*var == EQUAL)
			count_equals++;
		var++;
	}
	if (count_equals == 0 || count_equals > 1)
		status = 0;
	return (status);
}

/*
* PRE: env != NULL cmd != NULL
* POST: Si el node_env no existe lo agrega al env, en caso de que
*		exista sobreescribe el value.
*/
static int	overwrite_env(t_env **env, char **cmd, t_env *node_env)
{
	if (!node_env)
	{
		node_env = get_new_node_env(NULL, NULL);
		if (!node_env)
			return (ERROR);
		if (set_node_content(*cmd, &node_env) != SUCCESS)
			return (ERROR);
		add_back_to_env(env, node_env);
	}
	else
	{
		if (set_node_content(*cmd, &node_env) != SUCCESS)
			return (ERROR);
	}
	return (SUCCESS);
}

/*
* PRE: minishell != NULL && cmd != NULL
* POST: Ejecuta el builtin export de la minishell.
*		Devolviendo el status de la operacion.
*/
int	builtin_export(t_minishell *minishell, char **cmd)
{
	char	*key_var_cmd;
	t_env	*tmp;

	if (!cmd[1])
		return (print_env(minishell->env, MODE_EXPORT), SUCCESS);
	while (*cmd)
	{
		if (is_valid_var_format(*cmd))
		{
			key_var_cmd = ft_substr(*cmd, 0, get_len_key_var(*cmd));
			if (!key_var_cmd)
				return (ERROR);
			tmp = get_var_env(minishell->env, key_var_cmd);
			if (overwrite_env(&minishell->env, cmd, tmp) != SUCCESS)
				return (ERROR);
			free(key_var_cmd);
		}
		cmd++;
	}
	return (SUCCESS);
}
