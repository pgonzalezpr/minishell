/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsaiago- <bsaiago-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:30:57 by brayan            #+#    #+#             */
/*   Updated: 2024/02/21 14:17:14 by bsaiago-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: minishell != NULL && cmd != NULL
* POST: Ejecuta el builtin export de la minishell.
*		Devolviendo el status de la operacion.
*/
int	builtin_export(t_minishell *minishell, char **cmd)
{
	(void)minishell;
	(void)cmd;
	//return (status);
	return (1);
}
