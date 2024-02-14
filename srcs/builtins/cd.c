/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:34:18 by brayan            #+#    #+#             */
/*   Updated: 2024/02/14 23:27:23 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: cmd != NULL && path != NULL
* POST: Gestiona el caso para un path de ruta relativa.
*/
static void	case_relative_path(t_minishell *minishell, char **cmd, char *path)
{
	if (!minishell->cwd)
	{
		minishell->cwd = getcwd(NULL, 0);
		if (!minishell->cwd)
		{
			perror(RED MSG_GET_CWD DEF_COLOR);
			return ;
		}
	}
	ft_strlcpy(path, minishell->cwd, sizeof(path));
	ft_strlcat(path, (const char *)FOWARD_SLAH, sizeof(path));
	ft_strlcat(path, cmd[1], sizeof(path));
	if (chdir(path) != 0)
		perror(RED MSG_CD_FAILS DEF_COLOR);
	else
		update_vars_path_and_old_path(minishell, getenv(VAR_PWD), path);
}

/*
* PRE: -
* POST: Gestiona el caso para un path de ruta absoluta.
*/
static void	case_absolute_path(t_minishell *minishell, char **cmd)
{
	if (chdir(cmd[1]) != 0)
		perror(RED MSG_CD_FAILS DEF_COLOR);
	else
		update_vars_path_and_old_path(minishell, getenv(VAR_PWD), cmd[1]);
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
		update_vars_path_and_old_path(minishell, getenv(VAR_PWD),
			getcwd(NULL, 0));
	minishell->cwd = getenv(VAR_PWD);
}

/*
* PRE: minishell != NULL
* POST: Maneja el builtin cd controlando todos los casos
*		(cd .., cd path_relative, cd path_absolute)
*/
void	builtin_cd(t_minishell *minishell, char **cmd)
{
	char	path[1024];

	if (!cmd || !*cmd || !cmd[1])
	{
		fprintf(stderr, RED MSG_CD_MISSING_ARGS DEF_COLOR);
		return ;
	}
	else if (get_total_commands(minishell->cmd_line) > 2)
	{
		fprintf(stderr, RED MSG_MORE_THAN_TWO_ARGS_CD DEF_COLOR);
		return ;
	}
	else if (ft_strncmp(cmd[1], BACK_CD, 2) == 0)
		case_go_back(minishell);
	else if (cmd[1][0] == FOWARD_SLAH)
		case_absolute_path(minishell, cmd);
	else
		case_relative_path(minishell, cmd, path);
}
