/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:38:56 by brayan            #+#    #+#             */
/*   Updated: 2024/03/05 01:31:32 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: minishell != NULL
* POST: Muestra en terminal el cwd (Current Working Directory),
*		Devolviendo el status de la operacion.
*/
int	builtin_pwd(void)
{
	char	cwd[MAX_PATH];

	if (!getcwd(cwd, sizeof(cwd)))
		return (ERROR);
	printf("%s\n", cwd);
	return (SUCCESS);
}
