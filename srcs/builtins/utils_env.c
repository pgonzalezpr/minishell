/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsaiago- <bsaiago-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 22:26:59 by brayan            #+#    #+#             */
/*   Updated: 2024/04/13 17:45:33 by bsaiago-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_value_var_env(char **env, char *key)
{
	int		len_key_var_env;
	char	*key_env;
	char	*value;

	if (!key || !env || !*env)
		return (NULL);
	while (*env)
	{
		len_key_var_env = get_len_key_var(*env);
		key_env = ft_substr(*env, 0, len_key_var_env);
		if (!key_env)
			return (NULL);
		if (ft_strequals(key, key_env))
		{
			free(key_env);
			value = ft_strchr(*env, EQUAL);
			if (!value)
				return (NULL);
			return (value + 1);
		}
		free(key_env);
		env++;
	}
	return (NULL);
}

void	print_env(char **env, char mode)
{
	int		i;

	while (*env)
	{
		i = 0;
		if (mode == MODE_EXPORT)
		{
			printf(MSG_DECLARE);
			while ((*env)[i] && (*env)[i] != EQUAL)
				printf("%c", (*env)[i++]);
			if ((*env)[i] == EQUAL)
				printf("=%c%s%c", DOUBLE_QUOTE, ((*env) + i + 1), \
					DOUBLE_QUOTE);
			printf("\n");
		}
		else if (ft_strchr(*env, EQUAL))
			printf("%s\n", *env);
		env++;
	}
}

int	get_len_env(char **env)
{
	int		len;

	len = 0;
	while (env[len])
		len++;
	return (len);
}

int	get_cpy_env(char ***env_cpy, char **env_original,
int total_cpy, int pos_not_cpy)
{
	int	i;
	int	j;

	if (!env_cpy || !env_original || total_cpy <= 0)
		return (ERROR);
	(*env_cpy) = (char **)malloc(sizeof(char *) * (total_cpy + 1));
	if (!(*env_cpy))
		return (ERROR);
	i = 0;
	j = 0;
	while (env_original[i] && j < total_cpy)
	{
		if (pos_not_cpy != i)
		{
			(*env_cpy)[j] = ft_strdup(env_original[i]);
			if (!(*env_cpy)[j])
				return (free_env(*env_cpy, j), ERROR);
			j++;
		}
		i++;
	}
	(*env_cpy)[j] = NULL;
	return (SUCCESS);
}

void	free_env(char **env, int size)
{
	while (size-- > 0)
		free(env[size]);
	free(env);
}
