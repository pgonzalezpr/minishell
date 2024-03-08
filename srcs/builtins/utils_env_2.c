/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:14:42 by brayan            #+#    #+#             */
/*   Updated: 2024/03/07 01:47:23 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/* 
* PRE: -
* POST: Devuelve la longitud de la clave del env.
*/
int	get_len_key_var(char *key)
{
	int	len;

	len = 0;
	while (*key && *key != EQUAL)
	{
		len++;
		key++;
	}
	return (len);
}

/* 
* PRE: -
* POST: Devuelve una nueva variable con el key y value recibidos,
*		por parametros.
*/
char	*get_new_var(char *key, char *value)
{
	int		i;
	char	*new_var;

	if (!value || !key)
		return (NULL);
	new_var = (char *)malloc(ft_strlen(key) + ft_strlen(value) + 2);
	if (!new_var)
		return (NULL);
	i = 0;
	while (*key)
	{
		new_var[i++] = *key;
		key++;
	}
	new_var[i++] = EQUAL;
	while (*value)
	{
		new_var[i++] = *value;
		value++;
	}
	new_var[i++] = NULL_STR;
	return (new_var);
}

/*
* PRE: -
* POST: Devolvera la 
*		content == key, en caso de que no la encuentre, 
*		devolvera NULL
*/
int	get_pos_var_env(char **env, char *key)
{
	int		len_key_var_env;
	int		i;
	char	*key_env;

	if (!key || !env || !*env)
		return (POS_NOT_FOUNDED);
	i = 0;
	while (env[i])
	{
		len_key_var_env = get_len_key_var(env[i]);
		key_env = ft_substr(env[i], 0, len_key_var_env);
		if (!key_env)
			return (POS_NOT_FOUNDED);
		if (ft_strequals(key_env, key))
			return (free(key_env), i);
		free(key_env);
		i++;
	}
	return (POS_NOT_FOUNDED);
}

/*
* PRE: var != NULL
* POST: Devuelve true si el key es valido
*		key, KEY, KEY___KEY, KEY_key, __key_key, key1_
*/
int	is_valid_key_format(char *key)
{
	if (!key || (!ft_isalpha(key[0]) && key[0] != UNDERSCORE))
		return (0);
	if (!ft_isalpha(*key))
		return (0);
	key++;
	while (*key)
	{
		if (!ft_isalnum(*key) && *key != UNDERSCORE)
			return (0);
		key++;
	}
	return (1);
}
