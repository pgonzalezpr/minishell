/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:14:42 by brayan            #+#    #+#             */
/*   Updated: 2024/03/04 19:22:22 by bsaiago-         ###   ########.fr       */
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
