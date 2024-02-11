/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:38:56 by brayan            #+#    #+#             */
/*   Updated: 2024/02/11 23:10:30 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
* PRE: minishell != NULL
* POST: Muestra en terminal el cwd (Current Working Directory).
*/
int	pwd_cmd(char **cwd)
{
	(*cwd) = getcwd(NULL, 0);
	if (!(*cwd) || !cwd)
		return (EXIT_FAILURE);
	printf("%s\n", (*cwd));
	return (SUCCESS);
}
