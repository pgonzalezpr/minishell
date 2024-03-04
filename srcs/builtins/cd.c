/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:34:18 by brayan            #+#    #+#             */
/*   Updated: 2024/03/04 05:58:45 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: -
* POST: Gestiona el caso para un path de ruta relativa, devolviendo
*		el estado de la operacion.
*/
static int	case_relative_path(char ***env, char **cmd, \
int idx_pwd, int idx_oldpwd)
{
	char	path[MAX_PATH];
	char	*cwd;

	cwd = getcwd(path, MAX_PATH);
	if (!cwd)
		return (printf(RED MSG_GET_CWD DEF_COLOR), SUCCESS);
	ft_strlcpy(path, cwd, MAX_PATH);
	if (cmd[1][1] && (cwd[0] == FORWARD_SLAH && cwd[1]))
		ft_strlcat(path, FORWARD_SLAH_ST, MAX_PATH);
	ft_strlcat(path, cmd[1], MAX_PATH);
	if (chdir(path) != 0)
		return (printf("bash: cd: %s: No such file or directory\n", cmd[1]), 0);
	return (update_cd_vars(env, idx_oldpwd, idx_pwd, path));
}

/*
* PRE: -
* POST: Gestiona el caso para un path de ruta absoluta,
*		devolviendo el estado de la operacion.
*/
static int	case_absolute_path(char ***env, char **cmd, \
int idx_pwd, int idx_oldpwd)
{
	if (chdir(cmd[1]) != 0)
		return (printf(RED MSG_CD_FAILS DEF_COLOR), SUCCESS);
	return (update_cd_vars(env, idx_oldpwd, idx_pwd, cmd[1]));
}

/*
* PRE: -
* POST: Gestiona el caso para cd .. y devuelve el estado 
*		de la operacion
*/
static int	case_go_back(char ***env, int idx_pwd, int idx_oldpwd)
{
	char	cwd[MAX_PATH];

	if (!getcwd(cwd, sizeof(cwd)))
		return (ERROR);
	if (chdir(BACK_CD) != 0)
		return (perror(RED MSG_CD_FAILS DEF_COLOR), SUCCESS);
	return (update_cd_vars(env, idx_oldpwd, idx_pwd, cwd));
}

/*
* PRE: -
* POST: Gestiona el caso para cd sin parametros.
*/
static int	case_go_home(char ***env, int idx_pwd, int idx_oldpwd)
{
	char	*var_home;	
	int		pos_var_home;

	pos_var_home = get_pos_var_env(*env, VAR_HOME);
	if (pos_var_home == POS_NOT_FOUNDED)
		return (printf(MSG_HOME_UNSET), SUCCESS);
	var_home = ft_strchr((*env)[pos_var_home], EQUAL);
	var_home++;
	if (chdir (var_home) != 0)
		return (SUCCESS);
	return (update_cd_vars(env, idx_oldpwd, idx_pwd, var_home));
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
	int		idx_pwd;
	int		idx_oldpwd;

	if (!cmd || !*cmd)
		return (ERROR);
	if (get_total_commands(minishell->cmd_line) > 2)
	{
		printf(RED MSG_MORE_THAN_TWO_ARGS_CD DEF_COLOR);
		return (SUCCESS);
	}
	if (check_vars_cd(&minishell->envp, &idx_pwd, &idx_oldpwd) != SUCCESS)
		return (ERROR);
	if (!cmd[1])
		status = case_go_home(&minishell->envp, idx_pwd, idx_oldpwd);
	else if (ft_strcmp(cmd[1], BACK_CD) == 0)
		status = case_go_back(&minishell->envp, idx_pwd, idx_oldpwd);
	else if (cmd[1][0] == FORWARD_SLAH)
		status = case_absolute_path(&minishell->envp, cmd, idx_pwd, idx_oldpwd);
	else
		status = case_relative_path(&minishell->envp, cmd, idx_pwd, idx_oldpwd);
	return (status);
}
