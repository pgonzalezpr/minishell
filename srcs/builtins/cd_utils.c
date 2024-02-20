/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 19:03:57 by brayan            #+#    #+#             */
/*   Updated: 2024/02/20 04:53:06 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: -
* POST: Actualiza las variables de entorno OLDPWD o PWD
*		segun sea el nombre de la variable recibido por parametro,
*		devolviendo el status.	
*/
static int	update_var(t_minishell *minishell, char *path,
int index, char *var_name)
{
	char	*var;
	int		len;

	len = ft_strlen(path) + ft_strlen(var_name) + 1;
	free(minishell->env[index]);
	var = (char *)malloc(len);
	if (!var)
		return (perror(RED ERROR_MALLOC DEF_COLOR), ERROR);
	ft_strlcpy(var, var_name, len);
	ft_strlcat(var, path, len);
	minishell->env[index] = var;
	if (!minishell->env[index])
		return (perror(RED ERROR_MALLOC DEF_COLOR), ERROR);
	return (SUCCESS);
}

/*
* PRE: -
* POST: Agrega la variable pwd al env, devolviendo el status.
*/
static int	add_var_pwd_to_env(t_minishell *minishell, char **aux_old_env,
	char *new_path)
{
	int	len_old_env;

	len_old_env = get_len_matrix(minishell->env);
	get_ncpy_env(minishell, aux_old_env, len_old_env + 1);
	minishell->env[len_old_env] = ft_strdup(new_path);
	if (!minishell->env[len_old_env])
		return (perror(RED ERROR_MALLOC DEF_COLOR), ERROR);
	return (SUCCESS);
}

/*
* PRE: -
* POST: Agrega la variable oldpwd al env, devolviendo el status
*/
static int	add_var_oldpwd_to_env(t_minishell *minishell, char **aux_old_env,
	char *old_path)
{
	int	len_old_env;

	len_old_env = get_len_matrix(minishell->env);
	if (aux_old_env)
		free_matrix(aux_old_env, get_len_matrix(aux_old_env));
	aux_old_env = minishell->env;
	get_ncpy_env(minishell, aux_old_env, len_old_env + 1);
	minishell->env[len_old_env] = ft_strdup(old_path);
	if (!minishell->env[len_old_env])
		return (perror(RED ERROR_MALLOC DEF_COLOR), ERROR);
	free_matrix(aux_old_env, get_len_matrix(aux_old_env));
	return (SUCCESS);
}

/*
* PRE: -
* POST: Actualiza las variables de entorno OLDPWD & PWD de la minishell,
*		Devolviendo el estado de la operacion
*		s = Status
*/
int	update_vars_path_and_old_path(t_minishell *minishell,
	char *old_path, char *new_path)
{
	int		s;
	int		index_old_path;
	int		index_new_path;
	char	**aux_old_env;

	index_old_path = get_pos_var_env(minishell->env, VAR_OLDPWD);
	index_new_path = get_pos_var_env(minishell->env, VAR_PWD);
	aux_old_env = NULL;
	if (index_new_path != POS_NOT_FOUNDED)
		s = update_var(minishell, new_path, index_new_path, VAR_PWD_WITH_EQUAL);
	else if (index_new_path == POS_NOT_FOUNDED)
	{
		aux_old_env = minishell->env;
		s = add_var_pwd_to_env(minishell, aux_old_env, new_path);
	}
	if (index_old_path != POS_NOT_FOUNDED && s != SUCCESS)
		s = update_var(minishell, old_path, index_old_path, \
			VAR_OLDPWD_WITH_EQUAL);
	else if (index_old_path == POS_NOT_FOUNDED && s != SUCCESS)
	{
		if (aux_old_env)
			free_matrix(aux_old_env, get_len_matrix(aux_old_env));
		s = add_var_oldpwd_to_env(minishell, aux_old_env, old_path);
	}
	printf("PWD:%s\n", minishell->env[index_new_path]);
	printf("OLDPWD:%s\n", minishell->env[index_old_path]);
	return (s);
}
