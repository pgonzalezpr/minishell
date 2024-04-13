/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsaiago- <bsaiago-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:34:18 by brayan            #+#    #+#             */
/*   Updated: 2024/04/13 17:43:42 by bsaiago-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	case_relative_path(char ***env, char **cmd)
{
	char	path[MAX];
	char	*cwd;

	cwd = getcwd(path, MAX);
	if (!cwd)
		return (ft_putstr_fd(MSG_GET_CWD, STDERR_FILENO), SUCCESS);
	ft_strlcpy(path, cwd, MAX);
	if (cmd[1][1] && (cwd[0] == FORWARD_SLAH && cwd[1]))
		ft_strlcat(path, FORWARD_SLAH_ST, MAX);
	ft_strlcat(path, cmd[1], MAX);
	if (check_access_to_path(path) == ERROR)
		return (SUCCESS);
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(cmd[1], STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (1);
	}
	remove_foward_slash(path);
	return (update_cd_vars(env, getcwd(path, MAX)));
}

static int	case_absolute_path(char ***env, char *path)
{
	remove_foward_slash(path);
	if (check_access_to_path(path) == ERROR)
		return (SUCCESS);
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (1);
	}
	return (update_cd_vars(env, getcwd(path, MAX)));
}

static int	case_go_back(char ***env)
{
	char	cwd[MAX];

	if (check_access_to_path(BACK_CD) == ERROR)
		return (SUCCESS);
	if (chdir(BACK_CD) != 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(cwd, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (1);
	}
	if (!getcwd(cwd, MAX))
		return (ERROR);
	return (update_cd_vars(env, cwd));
}

static int	case_go_home(char ***env)
{
	char	*path_home;	

	path_home = get_value_var_env(*env, VAR_HOME);
	if (!path_home)
		return (ft_putstr_fd(MSG_HOME_UNSET, STDERR_FILENO), SUCCESS);
	if (check_access_to_path(path_home) == ERROR)
		return (SUCCESS);
	if (chdir (path_home) != 0)
		return (SUCCESS);
	return (update_cd_vars(env, path_home));
}

int	builtin_cd(t_minishell *minishell, char **cmd)
{
	int		status;

	status = SUCCESS;
	if (!cmd || !*cmd)
		return (ERROR);
	if (get_len_argv(cmd) > 2)
		return (ft_putstr_fd(MSG_TOO_MANY_ARGS_CD, STDERR_FILENO), status);
	if (!cmd[1])
		status = case_go_home(&minishell->envp);
	else if (ft_strequals(cmd[1], BACK_CD) && cmd[1][1])
		status = case_go_back(&minishell->envp);
	else if (cmd[1][0] == FORWARD_SLAH)
		status = case_absolute_path(&minishell->envp, cmd[1]);
	else if (cmd[1][0] != CURRENT_DIRECTORY)
		status = case_relative_path(&minishell->envp, cmd);
	return (status);
}
