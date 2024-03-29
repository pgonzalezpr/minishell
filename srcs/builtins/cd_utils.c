/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 03:17:41 by brayan            #+#    #+#             */
/*   Updated: 2024/03/29 17:51:15 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: -
* POST: Remueve el ultimo / del path enviado por parametro.
*/
void	remove_foward_slash(char path[MAX])
{
	int	len_path;

	if (!path)
		return ;
	len_path = ft_strlen(path);
	if (path[len_path - 1] && path[len_path - 1] == FORWARD_SLAH)
		path[len_path - 1] = NULL_STR;
}

/*
* PRE: -
* POST: Chequea el acceso del comando cd a la ruta path.
*/
int	check_access_to_path(char *path)
{
	if (!path)
		return (ERROR);
	if (access(path, F_OK) == ERROR)
		return (ft_putstr_fd(MSG_CD_NO_SUCH_FILE, STDERR_FILENO), ERROR);
	if (access(path, X_OK) == ERROR)
		return (ft_putstr_fd(MSG_CD_PERMISSION_DENIED, 2), ERROR);
	return (SUCCESS);
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
			return (SUCCESS);
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
