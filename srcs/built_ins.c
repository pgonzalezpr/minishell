/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:06:06 by brayan            #+#    #+#             */
/*   Updated: 2024/02/10 02:00:28 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	select_builtint(t_minishell *minishell)
{
	if (ft_strncmp(minishell->cmd_line, EXIT_CMD, 4) == 0)
	{
		rl_clear_history();
		exit_minishell(minishell, NULL, EXIT_SUCCESS);
	}
	else if (ft_strncmp(minishell->cmd_line, ECHO_CMD, 4) == 0)
		echo_cmd(minishell);
	else if (ft_strncmp(minishell->cmd_line, CD_CMD, 2) == 0)
		cd_cmd(minishell);
	else if (ft_strncmp(minishell->cmd_line, ENV_CMD, 3) == 0)
		env_cmd(minishell);
	else if (ft_strncmp(minishell->cmd_line, EXPORT_CMD, 6) == 0)
		export_cmd(minishell);
	else if (ft_strncmp(minishell->cmd_line, PWD_CMD, 3) == 0)
		pwd_cmd(minishell);
	else if (ft_strncmp(minishell->cmd_line, UNSET_CMD, 5) == 0)
		unset_cmd(minishell);
}
