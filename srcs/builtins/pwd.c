/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:38:56 by brayan            #+#    #+#             */
/*   Updated: 2024/03/29 22:48:23 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: minishell != NULL
* POST: Muestra en terminal el cwd (Current Working Directory),
*		Devolviendo el status de la operacion.
*/
int	builtin_pwd(int total_args)
{
	char	cwd[MAX];

	if (total_args == 1)
	{
		if (!getcwd(cwd, MAX))
			return (ft_putstr_fd(MSG_GET_CWD, STDERR_FILENO), ERROR);
		printf("%s\n", cwd);
	}
	else
		ft_putstr_fd(MSG_TOO_MANY_ARGS_PWD, STDERR_FILENO);
	return (SUCCESS);
}
