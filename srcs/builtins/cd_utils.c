/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 03:17:41 by brayan            #+#    #+#             */
/*   Updated: 2024/03/05 20:05:30 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: -
* POST: Actualiza el valor de las variables de entorno OLDPWD y PWD.
*/
void	remove_foward_slash(char path[MAX_PATH])
{
	int	len_path;

	len_path = ft_strlen(path);
	if (path[len_path - 1] && path[len_path - 1] == FORWARD_SLAH)
		path[len_path - 1] = NULL_STR;
}

/*
* PRE: -
* POST: Actualiza el valor de las variables de entorno OLDPWD y PWD.
*/
int	update_cd_vars(char ***env, char *new_value_pwd)
{
	char	*old_value_pwd;
	int		pos_var_pwd;
	int		pos_var_oldpwd;

	pos_var_pwd = get_pos_var_env(*env, VAR_PWD);
	pos_var_oldpwd = get_pos_var_env(*env, VAR_OLDPWD);
	if (pos_var_pwd != POS_NOT_FOUNDED)
	{
		old_value_pwd = get_value_var_env(*env, VAR_PWD);
		if (!old_value_pwd)
			return (ERROR);
	}
	if (pos_var_oldpwd != POS_NOT_FOUNDED)
	{
		free((*env)[pos_var_oldpwd]);
		(*env)[pos_var_oldpwd] = get_new_var(VAR_OLDPWD, old_value_pwd);
		if (!(*env)[pos_var_oldpwd])
			return (ERROR);
		free((*env)[pos_var_pwd]);
		(*env)[pos_var_pwd] = get_new_var(VAR_PWD, new_value_pwd);
		if (!(*env)[pos_var_pwd])
			return (ERROR);
	}
	return (SUCCESS);
}
