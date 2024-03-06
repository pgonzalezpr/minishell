/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 01:55:42 by brayan            #+#    #+#             */
/*   Updated: 2024/03/06 03:54:20 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	protect_handle_signals_configure(void)
{
	int	status;

	status = SUCCESS;
	if (configure_handle_signals(SIGINT, signal_handler) == ERROR)
		status = ERROR;
	if (configure_handle_signals(SIGQUIT, signal_handler) == ERROR)
		status = ERROR;
	if (configure_handle_signals(SIGTERM, signal_handler) == ERROR)
		status = ERROR;
	return (status);
}

int	configure_handle_signals(int nb_signal, void (*handler)(int))
{
	if (signal(nb_signal, handler) == SIG_ERR)
		return (ERROR);
	return (SUCCESS);
}
