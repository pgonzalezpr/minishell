/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 16:14:42 by brayan            #+#    #+#             */
/*   Updated: 2024/03/03 21:55:14 by brayan           ###   ########.fr       */
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
