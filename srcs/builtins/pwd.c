/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:38:56 by brayan            #+#    #+#             */
/*   Updated: 2024/03/09 03:32:21 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: minishell != NULL
* POST: Muestra en terminal el cwd (Current Working Directory),
*		Devolviendo el status de la operacion.
*/
int	builtin_pwd(int total_commands)
{
	char	cwd[MAX];

	if (total_commands == 1)
	{
		if (!getcwd(cwd, MAX))
			return (printf(MSG_GET_CWD), ERROR);
		printf("%s\n", cwd);
	}
	else
		printf(MSG_TOO_MANY_ARGS_PWD);
	return (SUCCESS);
}
