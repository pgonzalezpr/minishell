/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:38:56 by brayan            #+#    #+#             */
/*   Updated: 2024/02/10 04:40:34 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
* PRE: minishell != NULL
* POST: Muestra en terminal el cwd (Current Working Directory).
*/
void	pwd_cmd()
{
  	char *cwd = getcwd(NULL, 0);
  	if (cwd == NULL) 
	{
    	perror("getcwd fails");
    	exit(EXIT_FAILURE);
  	}
	printf("%s\n", cwd);
}
