/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 19:03:57 by brayan            #+#    #+#             */
/*   Updated: 2024/02/23 01:46:00 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: -
* POST: Actualiza las variables de entorno OLDPWD & PWD de la minishell,
*		Devolviendo el estado de la operacion
*		s = Status
*/
int	update_cd_vars(t_minishell *minishell)
{
	char	*cwd;
	t_env	*oldpwd;
	t_env 	*pwd;

	oldpwd = get_var_env(minishell->env, VAR_OLDPWD);
	if (oldpwd)
		del_node_env(minishell->env, oldpwd);
	pwd = get_var_env(minishell->env, VAR_PWD);
	if (pwd)
		del_node_env(minishell->env, pwd);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ERROR);
	oldpwd = get_new_node_env(VAR_OLDPWD, minishell->cwd);
	if (!oldpwd)
		return (ERROR);
	pwd = get_new_node_env(VAR_PWD, cwd);
	if (!pwd)
		return (ERROR);
	add_back_to_env(&minishell->env, oldpwd);
	add_back_to_env(&minishell->env, pwd);
	return (SUCCESS);
}
