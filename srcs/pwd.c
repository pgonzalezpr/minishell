/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:38:56 by brayan            #+#    #+#             */
/*   Updated: 2024/02/10 03:54:10 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
* PRE: minishell != NULL
* POST: 
*/
void	pwd_cmd(t_minishell *minishell)
{
	(void)minishell;
	printf("PWD\n");
}
