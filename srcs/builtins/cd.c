/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:34:18 by brayan            #+#    #+#             */
/*   Updated: 2024/03/08 05:13:42 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: -
* POST: Gestiona el caso para un path de ruta relativa, devolviendo
*		el estado de la operacion.
*/
static int	case_relative_path(char ***env, char **cmd)
{
	char	path[MAX];
	char	*cwd;

	cwd = getcwd(path, MAX);
	if (!cwd)
		return (printf(RED MSG_GET_CWD DEF_COLOR), SUCCESS);
	ft_strlcpy(path, cwd, MAX);
	if (cmd[1][1] && (cwd[0] == FORWARD_SLAH && cwd[1]))
		ft_strlcat(path, FORWARD_SLAH_ST, MAX);
	ft_strlcat(path, cmd[1], MAX);
	if (check_access_to_path(path) == ERROR)
		return (SUCCESS);
	if (chdir(path) != 0)
		return (printf("minishell: cd: %s: No such file or directory\n", \
					cmd[1]), 1);
	remove_foward_slash(path);
	return (update_cd_vars(env, getcwd(path, MAX)));
}

/*
* PRE: -
* POST: Gestiona el caso para un path de ruta absoluta,
*		devolviendo el estado de la operacion.
*/
static int	case_absolute_path(char ***env, char *path)
{
	remove_foward_slash(path);
	if (check_access_to_path(path) == ERROR)
		return (SUCCESS);
	if (chdir(path) != 0)
		return (printf("bash: cd: %s: No such file or directory\n", path), 1);
	return (update_cd_vars(env, getcwd(path, MAX)));
}

/*
* PRE: -
* POST: Gestiona el caso para cd .. y devuelve el estado 
*		de la operacion
*/
static int	case_go_back(char ***env)
{
	char	cwd[MAX];

	if (check_access_to_path(BACK_CD) == ERROR)
		return (SUCCESS);
	if (chdir(BACK_CD) != 0)
		return (printf("bash: cd: %s: No such file or directory\n", cwd), 1);
	if (!getcwd(cwd, MAX))
		return (ERROR);
	return (update_cd_vars(env, cwd));
}

/*
* PRE: -
* POST: Gestiona el caso para cd sin parametros.
*/
static int	case_go_home(char ***env)
{
	char	*path_home;	

	path_home = get_value_var_env(*env, VAR_HOME);
	if (!path_home)
		return (printf(MSG_HOME_UNSET), SUCCESS);
	if (check_access_to_path(path_home) == ERROR)
		return (SUCCESS);
	if (chdir (path_home) != 0)
		return (SUCCESS);
	return (update_cd_vars(env, path_home));
}

/*
* PRE: minishell != NULL
* POST: Maneja el builtin cd controlando todos los casos
*		(cd, cd .., cd path_relative, cd path_absolute)
*		Devolviendo el estado de la operacion
*/
int	builtin_cd(t_minishell *minishell, char **cmd)
{
	int		status;

	//print_vars_cd(minishell->envp, minishell->cwd);
	status = SUCCESS;
	if (!cmd || !*cmd)
		return (ERROR);
	if (get_total_commands(minishell->cmd_line) > 2)
		return (printf(MSG_TOO_MANY_ARGS_CD), status);
	if (!cmd[1])
		status = case_go_home(&minishell->envp);
	else if (ft_strequals(cmd[1], BACK_CD) && cmd[1][1])
		status = case_go_back(&minishell->envp);
	else if (cmd[1][0] == FORWARD_SLAH)
		status = case_absolute_path(&minishell->envp, cmd[1]);
	else if (cmd[1][0] != CURRENT_DIRECTORY)
		status = case_relative_path(&minishell->envp, cmd);
	//print_vars_cd(minishell->envp, minishell->cwd);
	return (status);
}
