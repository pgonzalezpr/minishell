/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:40:02 by brayan            #+#    #+#             */
/*   Updated: 2024/02/22 16:32:16 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: minishell != NULL
* POST: Elimina las variables de entorno recibidas de cmd
*		en el env de la minishell, devolviendo el status
*		de la operacion.
*/
int	builtin_unset(t_minishell *minishell, char **cmd)
{
	(void)minishell;
	(void)cmd;
	//return (status);
	return (1);
}
