/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 19:03:57 by brayan            #+#    #+#             */
/*   Updated: 2024/02/18 05:22:34 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_vars_path_and_old_path(t_minishell *minishell,
	char *old_path, char *new_path)
{
	int		index_old_path;
	int		index_new_path;
	int		len_old_env;
	char	*var;
	char	**aux_old_env;

	index_old_path = get_pos_var_env(minishell->env, VAR_OLDPWD);
	index_new_path = get_pos_var_env(minishell->env, VAR_PWD);
	aux_old_env = NULL;
	if (index_new_path != POS_NOT_FOUNDED)
	{
		free(minishell->env[index_new_path]);
		var = (char *)malloc(4 + ft_strlen(new_path) + 1);
		if (!var)
		{
		}
		ft_strlcpy(var, VAR_PWD_WITH_EQUAL, 4 + ft_strlen(new_path) + 1);
		ft_strlcat(var, new_path, 4 + ft_strlen(new_path) + 1);
		minishell->env[index_new_path] = var;
		if (!minishell->env[index_new_path])
		{
		}
	}
	else
	{
		aux_old_env = minishell->env;
		len_old_env = get_len_matrix(minishell->env);
		get_ncpy_env(minishell, aux_old_env, len_old_env + 1);
		minishell->env[len_old_env] = ft_strdup(new_path);
		if (!minishell->env[len_old_env])
		{
			//PROTEGER
		}
		
	}
	if (index_old_path != POS_NOT_FOUNDED)
	{
		free(minishell->env[index_old_path]);
		var = (char *)malloc(7 + ft_strlen(old_path) + 1);
		if (!var)
		{
			// Handle error
		}
		ft_strlcpy(var, VAR_OLDPWD_WITH_EQUAL, 7 + ft_strlen(old_path) + 1);
		ft_strlcat(var, old_path, 7 + ft_strlen(old_path) + 1);
		minishell->env[index_old_path] = var;
		if (!minishell->env[index_old_path])
		{
			// Handle error
		}
	}
	else
	{
		if (aux_old_env)
			free_matrix(aux_old_env, get_len_matrix(aux_old_env));
		aux_old_env = minishell->env;
		len_old_env = get_len_matrix(minishell->env);
		get_ncpy_env(minishell, aux_old_env, len_old_env + 1);
		minishell->env[len_old_env] = ft_strdup(old_path);
		if (!minishell->env[len_old_env])
		{
			//PROTEGER
			
		}
		free_matrix(aux_old_env, get_len_matrix(aux_old_env));
	}
	minishell->cwd = old_path;
	printf("OLDPWD: %s\n", minishell->env[index_old_path]);
	printf("NEWPWD: %s\n", minishell->env[index_new_path]);
}
