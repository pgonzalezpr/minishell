/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 21:42:27 by brayan            #+#    #+#             */
/*   Updated: 2024/02/12 02:51:26 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
* PRE: -
* POST: inicializa el env.
*/
int	init_env(char **env, t_minishell *minishell)
{
	return (get_cpy_env(minishell, env));
}
