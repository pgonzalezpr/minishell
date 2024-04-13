/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsaiago- <bsaiago-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:40:02 by brayan            #+#    #+#             */
/*   Updated: 2024/04/13 17:44:59 by bsaiago-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_unset(t_minishell *minishell, char **cmd)
{
	char	**new_env;
	int		i;
	int		idx;
	int		len_env;
	int		status;

	i = 0;
	if (minishell->envp)
		len_env = get_len_env(minishell->envp);
	while (cmd[++i] && minishell->envp)
	{
		idx = get_pos_var_env(minishell->envp, cmd[i]);
		if (idx != POS_NOT_FOUNDED)
		{
			status = get_cpy_env(&new_env, minishell->envp, --len_env, idx);
			if (status == ERROR)
				return (ERROR);
			free_env(minishell->envp, len_env + 1);
			minishell->envp = new_env;
		}
	}
	return (SUCCESS);
}
