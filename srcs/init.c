/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 21:42:27 by brayan            #+#    #+#             */
/*   Updated: 2024/02/14 20:48:37 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
* PRE: -
* POST: inicializa el env.
*/
int	init_env(char **env, t_minishell *minishell)
{
	return (get_ncpy_env(minishell, env, get_len_matrix(env)));
}
