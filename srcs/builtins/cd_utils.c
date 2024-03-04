/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 03:17:41 by brayan            #+#    #+#             */
/*   Updated: 2024/03/04 05:29:40 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: -
* POST: Checkea si las variables de entorno (PWD Y OLDPWD) existen.
*/
int	check_vars_cd(char ***env, int *pos_var_pwd, int *pos_var_oldpwd)
{
	*pos_var_pwd = get_pos_var_env(*env, VAR_PWD);
	if (*pos_var_pwd == POS_NOT_FOUNDED)
		return (printf(MSG_PWD_UNSET), SUCCESS);
	*pos_var_oldpwd = get_pos_var_env(*env, VAR_OLDPWD);
	if (*pos_var_oldpwd == POS_NOT_FOUNDED)
		return (SUCCESS);
	return (SUCCESS);
}

/*
* PRE: -
* POST: Actualiza el valor de las variables de entorno OLDPWD y PWD.
*/
int	update_cd_vars(char ***env, int pos_var_oldpwd, int pos_var_pwd, \
char *new_value_pwd)
{
	char	*value_pwd;

	value_pwd = ft_strchr((*env)[pos_var_pwd], EQUAL);
	if (!value_pwd)
		return (ERROR);
	free((*env)[pos_var_oldpwd]);
	(*env)[pos_var_oldpwd] = get_new_var(VAR_OLDPWD, ++value_pwd);
	if (!(*env)[pos_var_oldpwd])
		return (ERROR);
	free((*env)[pos_var_pwd]);
	(*env)[pos_var_pwd] = get_new_var(VAR_PWD, new_value_pwd);
	if (!(*env)[pos_var_pwd])
		return (ERROR);
	return (SUCCESS);
}
