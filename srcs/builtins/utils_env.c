/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 22:26:59 by brayan            #+#    #+#             */
/*   Updated: 2024/03/04 00:14:19 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: -
* POST: Devolvera la variable del env que tenga el
*		content == key || content == value segun el parametro
*		de busqueda que corresponda, en caso de que no la encuentre, 
*		devolvera NULL
*/
int	get_pos_var_env(char **env, char *content)
{
	int		len_key_var;
	int		pos_var;
	char	*key_env;
	char	*value_env;

	pos_var = 0;
	while (env[pos_var])
	{
		len_key_var = get_len_key_var(content);
		key_env = ft_substr(env[pos_var], 0, len_key_var);
		if (!key_env)
			return (POS_NOT_FOUNDED);
		value_env = ft_substr(env[pos_var], len_key_var + 1, \
		ft_strlen(env[pos_var]) - len_key_var);
		if (!value_env)
			return (free(key_env), POS_NOT_FOUNDED);
		if (ft_strcmp(key_env, content) == 0
			|| ft_strcmp(value_env, content) == 0)
			return (free(key_env), free(value_env), pos_var);
		free(key_env);
		free(value_env);
		pos_var++;
	}
	return (POS_NOT_FOUNDED);
}

/*
* PRE: env != NULL
* POST: Imprime por consola las variables de entorno del minishell
*		segun el modo (MODE_ENV, MODE_EXPORT)
*/
void	print_env(char **env, char mode)
{
	while (*env)
	{
		if (mode == MODE_EXPORT)
			printf("declare -x ");
		if (mode == MODE_EXPORT || mode == MODE_ENV)
			printf("%s", *env);
		printf("\n");
		env++;
	}
}

/*
* PRE: env != NULL.
* POST: Devuelve la longitud del env.
*/
int	get_len_env(char **env)
{
	int		len;

	len = 0;
	while (env[len])
		len++;
	return (len);
}

/*
* PRE: -
* POST: Devuelve una copia del env indicando el total que
*		vamos a copiar. Si pos_not_copy == EMPTY
*		
*/
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

/*
* PRE: -
* POST: Libera la memoria del env.
*/
void	free_env(char **env, int size)
{
	while (size-- > 0)
		free(env[size]);
	free(env);
}
