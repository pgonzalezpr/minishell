/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 19:03:57 by brayan            #+#    #+#             */
/*   Updated: 2024/02/14 23:10:24 by brayan           ###   ########.fr       */
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
		var = (char *)malloc(ft_strlen(new_path) + 5);
		if (!var)
		{
			//PROTEGER
		}
		var[0] = NULL_STR;
		ft_strlcat(var, (const char *)VAR_PWD_WITH_EQUAL, 5);
		ft_strlcat(var, new_path, ft_strlen(new_path) + 5);
		minishell->env[index_new_path] = var;
		if (!minishell->env[index_new_path])
		{
			//PROTEGER
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
		var = (char *)malloc(ft_strlen(old_path) + 8);
		if (!var)
		{
			//PROTEGER
		}
		var[0] = NULL_STR;
		ft_strlcat(var, (const char *)VAR_OLDPWD_WITH_EQUAL, 8);
		ft_strlcat(var, old_path, ft_strlen(old_path) + 8);
		minishell->env[index_old_path] = var;
		if (!minishell->env[index_old_path])
		{
			//PROTEGER
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
}
