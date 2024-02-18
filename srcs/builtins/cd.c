/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:34:18 by brayan            #+#    #+#             */
/*   Updated: 2024/02/18 06:28:18 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: cmd != NULL && path != NULL
* POST: Gestiona el caso para un path de ruta relativa.
*/
void	case_relative_path(t_minishell *minishell, char **cmd)
{
	char	path[MAX_PATH];

	ft_strlcpy(path, minishell->cwd, sizeof(path));
	if (cmd[1][1])
		ft_strlcat(path, FOWARD_SLAH_STR, sizeof(path));
	ft_strlcat(path, cmd[1], sizeof(path));
	if (chdir(path) != 0)
		printf("bash: cd: %s: No such file or directory\n", cmd[1]);
	else
		update_vars_path_and_old_path(minishell, minishell->cwd, path);
}

/*
* PRE: -
* POST: Gestiona el caso para un path de ruta absoluta.
*/
static void	case_absolute_path(t_minishell *minishell, char **cmd)
{
	if (chdir(cmd[1]) != 0)
		printf("bash: cd: %s: No such file or directory\n", cmd[1]);
	else
		update_vars_path_and_old_path(minishell, minishell->cwd, cmd[1]);
}

/*
* PRE: -
* POST: Gestiona el caso para cd ..
*/
static void	case_go_back(t_minishell *minishell)
{
	if (chdir(BACK_CD) != 0)
		perror(RED MSG_CD_FAILS DEF_COLOR);
	else
		update_vars_path_and_old_path(minishell, minishell->cwd,
			getcwd(NULL, 0));
}

/*
* PRE: minishell != NULL
* POST: Maneja el builtin cd controlando todos los casos
*		(cd .., cd path_relative, cd path_absolute)
*/
void	builtin_cd(t_minishell *minishell, char **cmd)
{
	if (!cmd || !*cmd || !cmd[1])
	{
		fprintf(stderr, RED MSG_CD_MISSING_ARGS DEF_COLOR);
		return ;
	}
	if (get_total_commands(minishell->cmd_line) > 2)
	{
		fprintf(stderr, RED MSG_MORE_THAN_TWO_ARGS_CD DEF_COLOR);
		return ;
	}
	minishell->cwd = getcwd(NULL, 0);
	if (!minishell->cwd)
	{
		perror(RED MSG_GET_CWD DEF_COLOR);
		return ;
	}
	if (ft_strncmp(cmd[1], BACK_CD, 2) == 0)
		case_go_back(minishell);
	else if (cmd[1][0] == FOWARD_SLAH)
		case_absolute_path(minishell, cmd);
	else
		case_relative_path(minishell, cmd);
}
