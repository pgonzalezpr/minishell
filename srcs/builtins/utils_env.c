/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 22:26:59 by brayan            #+#    #+#             */
/*   Updated: 2024/03/07 02:14:45 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: -
* POST: Devolvera la 
*		content == key, en caso de que no la encuentre, 
*		devolvera NULL
*/
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

/*
* PRE: env != NULL
* POST: Imprime por consola las variables de entorno del minishell
*		segun el modo (MODE_ENV, MODE_EXPORT)
*/
void	print_env(char **env, char mode)
{
	int		i;

	while (*env)
	{
		i = 0;
		if (mode == MODE_EXPORT)
			printf(MSG_DECLARE);
		while ((*env)[i] && (*env)[i] != EQUAL)
		{
			printf("%c", (*env)[i]);
			i++;
		}
		if (mode == MODE_ENV)
			printf("%s\n", &((*env)[i]));
		else
			printf("=\"%s\"\n", &((*env)[++i]));
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
* POST: Copia env_original en env_cpy hasta lo que indique total_cpy
		, Si pos_not_copy == IGNORE, copiara todo el contenido de 
*		env_original en env_cpy, si es otro valor que este dentro de 
*		las posiciones del env_original, lo ignorara y no lo copiara.
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
