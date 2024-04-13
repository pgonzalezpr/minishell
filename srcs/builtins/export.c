/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsaiago- <bsaiago-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:30:57 by brayan            #+#    #+#             */
/*   Updated: 2024/04/13 17:44:38 by bsaiago-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_var_format(char *var)
{
	char	*key;

	if (!var)
		return (0);
	key = ft_substr(var, 0, get_len_key_var(var));
	if (!key)
		return (0);
	if (!is_valid_key_format(key))
	{
		ft_putstr_fd("minishell: export: '", STDERR_FILENO);
		ft_putstr_fd(var, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		return (free(key), INVALID_KEY);
	}
	free(key);
	return (1);
}

static char	**case_var_not_exist(char **env, char *new_var, int len_env)
{
	char	**new_env;
	int		status;

	status = get_cpy_env(&new_env, env, len_env + 1, IGNORE);
	if (status == ERROR)
		return (NULL);
	new_env[len_env + 1] = NULL;
	new_env[len_env] = ft_strdup(new_var);
	if (!new_env[len_env])
		return (NULL);
	return (new_env);
}

static char	**case_var_exist(char **env, char *new_var, int pos_var_env,
		int len_env)
{
	char	**new_env;
	int		status;

	status = get_cpy_env(&new_env, env, len_env, IGNORE);
	if (status == ERROR)
		return (NULL);
	free(new_env[pos_var_env]);
	new_env[pos_var_env] = ft_strdup(new_var);
	if (!new_env[pos_var_env])
		return (NULL);
	return (new_env);
}

static int	overwrite_env(t_minishell *minishell, char *new_var,
		int pos_var_env)
{
	int		len_env;
	char	**old_env;
	char	**new_env;

	len_env = get_len_env(minishell->envp);
	old_env = minishell->envp;
	if (pos_var_env != POS_NOT_FOUNDED)
		new_env = case_var_exist(old_env, new_var, pos_var_env, len_env);
	else
		new_env = case_var_not_exist(old_env, new_var, len_env);
	if (!new_env)
		return (ERROR);
	free_env(old_env, len_env);
	minishell->envp = new_env;
	return (SUCCESS);
}

int	builtin_export(t_minishell *minishell, char **cmd)
{
	int		pos_var_env;
	char	*key_var_cmd;

	if (!cmd[1])
		return (print_env(minishell->envp, MODE_EXPORT), SUCCESS);
	cmd++;
	while (*cmd)
	{
		if (check_var_format(*cmd) == 1)
		{
			key_var_cmd = ft_substr(*cmd, 0, get_len_key_var(*cmd));
			if (!key_var_cmd)
				return (ERROR);
			pos_var_env = get_pos_var_env(minishell->envp, key_var_cmd);
			if (overwrite_env(minishell, *cmd, pos_var_env) != SUCCESS)
				return (free(key_var_cmd), ERROR);
			free(key_var_cmd);
		}
		cmd++;
	}
	return (SUCCESS);
}
