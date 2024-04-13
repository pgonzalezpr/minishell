/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsaiago- <bsaiago-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 01:32:06 by brayan            #+#    #+#             */
/*   Updated: 2024/04/13 17:44:14 by bsaiago-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	builtin_env(t_minishell *minishell, int len)
{
	if (!minishell)
		return (ERROR);
	if (len == 1)
		print_env(minishell->envp, MODE_ENV);
	else
		ft_putstr_fd(MSG_TOO_MANY_ARGS_ENV, STDERR_FILENO);
	return (SUCCESS);
}
