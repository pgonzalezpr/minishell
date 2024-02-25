/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:34:18 by brayan            #+#    #+#             */
/*   Updated: 2024/02/25 23:54:22 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: -
* POST: Gestiona el caso para un path de ruta relativa, devolviendo
*		el estado de la operacion.
*/
static int	case_relative_path(t_env *env, char **cmd, \
char path[MAX_PATH])
{
	t_env	*pwd;
	t_env	*oldpwd;

	ft_strlcpy(path, getcwd(path, MAX_PATH), MAX_PATH);
	if (cmd[1][1] && (getcwd(path, MAX_PATH)[0] == FOWARD_SLAH \
		&& getcwd(path, MAX_PATH)[1]))
		ft_strlcat(path, FOWARD_SLAH_STR, MAX_PATH);
	ft_strlcat(path, cmd[1], MAX_PATH);
	if (chdir(path) != 0)
		return (printf("bash: cd: %s: No such file or directory\n", cmd[1]), 0);
	pwd = get_var_env(env, VAR_PWD);
	if (!pwd)
		return (printf(MSG_PWD_UNSET), SUCCESS);
	oldpwd = get_var_env(env, VAR_OLDPWD);
	if (!oldpwd)
		return (SUCCESS);
	free(oldpwd->value);
	oldpwd->value = ft_strdup(pwd->value);
	if (!oldpwd->value)
		return (ERROR);
	free(pwd->value);
	pwd->value = ft_strdup(path);
	if (!pwd->value)
		return (ERROR);
	return (SUCCESS);
}

/*
* PRE: -
* POST: Gestiona el caso para un path de ruta absoluta,
*		devolviendo el estado de la operacion.
*/
static int	case_absolute_path(t_env *env, char **cmd)
{
	t_env	*pwd;
	t_env	*oldpwd;

	pwd = get_var_env(env, VAR_PWD);
	if (!pwd)
		return (printf(MSG_PWD_UNSET), SUCCESS);
	oldpwd = get_var_env(env, VAR_OLDPWD);
	if (!oldpwd)
		return (SUCCESS);
	if (chdir(cmd[1]) != 0)
		return (perror(RED MSG_CD_FAILS DEF_COLOR), SUCCESS);
	free(oldpwd->value);
	oldpwd->value = ft_strdup(pwd->value);
	if (!oldpwd->value)
		return (ERROR);
	free(pwd->value);
	pwd->value = ft_strdup(cmd[1]);
	if (!pwd->value)
		return (perror(RED MSG_CD_FAILS DEF_COLOR), ERROR);
	return (SUCCESS);
}

/*
* PRE: -
* POST: Gestiona el caso para cd .. y devuelve el estado 
*		de la operacion
*/
static int	case_go_back(t_env *env)
{
	t_env	*pwd;
	t_env	*oldpwd;

	pwd = get_var_env(env, VAR_PWD);
	if (!pwd)
		return (printf(MSG_PWD_UNSET), SUCCESS);
	oldpwd = get_var_env(env, VAR_OLDPWD);
	if (!oldpwd)
		return (SUCCESS);
	if (chdir(BACK_CD) != 0)
		return (perror(RED MSG_CD_FAILS DEF_COLOR), SUCCESS);
	free(oldpwd->value);
	oldpwd->value = ft_strdup(pwd->value);
	if (!oldpwd->value)
		return (ERROR);
	free(pwd->value);
	pwd->value = getcwd(NULL, 0);
	if (!pwd->value)
		return (perror(RED MSG_CD_FAILS DEF_COLOR), ERROR);
	return (SUCCESS);
}

/*
* PRE: -
* POST: Gestiona el caso para cd sin parametros.
*/
static int	case_go_home(t_env *env)
{
	t_env	*pwd;
	t_env	*oldpwd;
	t_env	*home;

	pwd = get_var_env(env, VAR_PWD);
	if (!pwd)
		return (printf(MSG_PWD_UNSET), SUCCESS);
	home = get_var_env(env, VAR_HOME);
	if (!home)
		return (SUCCESS);
	if (chdir(home->value) != 0)
		return (perror(RED MSG_CD_FAILS DEF_COLOR), SUCCESS);
	oldpwd = get_var_env(env, VAR_OLDPWD);
	if (!oldpwd)
		return (SUCCESS);
	free(oldpwd->value);
	oldpwd->value = ft_strdup(pwd->value);
	if (!oldpwd->value)
		return (ERROR);
	free(pwd->value);
	pwd->value = ft_strdup(home->value);
	if (!pwd->value)
		return (ERROR);
	return (SUCCESS);
}

/*
* PRE: minishell != NULL
* POST: Maneja el builtin cd controlando todos los casos
*		(cd .., cd path_relative, cd path_absolute)
*		Devolviendo el estado de la operacion
*/
int	builtin_cd(t_minishell *minishell, char **cmd)
{
	int		status;
	char	path[MAX_PATH];

	if (!cmd || !*cmd)
		return (ERROR);
	if (get_total_commands(minishell->cmd_line) > 2)
	{
		fprintf(stderr, RED MSG_MORE_THAN_TWO_ARGS_CD DEF_COLOR);
		return (SUCCESS);
	}
	if (!cmd[1])
		status = case_go_home(minishell->env);
	else if (ft_strncmp(cmd[1], BACK_CD, 2) == 0)
		status = case_go_back(minishell->env);
	else if (cmd[1][0] == FOWARD_SLAH)
		status = case_absolute_path(minishell->env, cmd);
	else
		status = case_relative_path(minishell->env, cmd, path);
	return (status);
}
