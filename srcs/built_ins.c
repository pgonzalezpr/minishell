/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:06:06 by brayan            #+#    #+#             */
/*   Updated: 2024/02/10 04:37:45 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
* PRE: minishell != NULL
* POST: Seleccionara el comando.
*/
void	select_builtint(t_minishell *minishell)
{
	char	**cmd;

	cmd = ft_split(minishell->cmd_line, ' ');
	if (!cmd || !*cmd)
	{
		// Handle memory fails
		return ;
	}
	if (ft_strncmp(minishell->cmd_line, EXIT_CMD, 4) == 0)
	{
		rl_clear_history();
		exit_minishell(minishell, NULL, EXIT_SUCCESS);
	}
	else if (ft_strncmp(cmd[0], ECHO_CMD, 4) == 0)
		echo_cmd(cmd);
	else if (ft_strncmp(cmd[0], CD_CMD, 2) == 0)
		cd_cmd(minishell);
	else if (ft_strncmp(cmd[0], ENV_CMD, 3) == 0)
		env_cmd(minishell);
	else if (ft_strncmp(cmd[0], EXPORT_CMD, 6) == 0)
		export_cmd(minishell);
	else if (ft_strncmp(cmd[0], PWD_CMD, 3) == 0)
		pwd_cmd();
	else if (ft_strncmp(cmd[0], UNSET_CMD, 5) == 0)
		unset_cmd(minishell);
}
