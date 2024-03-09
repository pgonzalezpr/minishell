/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 01:55:42 by brayan            #+#    #+#             */
/*   Updated: 2024/03/09 00:49:01 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
int	init_signal(int nb_signal, void (*handler)(int))
{
	struct sigaction	signal;
	struct termios		tc;

	sigemptyset(&signal.sa_mask);
	if (!handler)
	{
		signal.sa_handler = SIG_IGN;
		signal.sa_flags = SA_RESTART;
		if (sigaction(nb_signal, &signal, NULL) < 0)
			exit (1);
	else
	{
		signal.sa_flags = SA_RESTART | SA_SIGINFO;
		tcgetattr(0, &tc);
		tc.c_lflag &= ~ECHOCTL;
		tcsetattr(0, TCSANOW, &tc);
		//signal.sa_sigaction = CASO_INTERACITO;
		//signal.sa_sigaction = CASO NOINTERACTIVO;
		sigaction(SIGINT, &signal, NULL);
		sigaction(SIGQUIT, &signal, NULL);
		if (sigaction(nb_signal, SIG_IGN) == SIG_ERR)
			return (ERROR);
	}
	return (SUCCESS);
}
*/

/*
void	handle_sigint(int sig, siginfo_t *info, void *handler)
{
	(void)info;
	(void)handler;
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 1;
	}
}

void	h_handle(int sig, siginfo_t *info, void *handler)
{
	(void)info;
	(void)handler;
	if (sig == SIGINT)
	{
		g_exit_status = 1;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		exit(EXIT_SUCCESS);
	}
}
*/

/*
void	exec_ignore_signal(int signum)
{
	struct sigaction	signal;

	signal.sa_handler = SIG_IGN;
	signal.sa_flags = SA_RESTART;
	sigemptyset(&signal.sa_mask);
	if (sigaction(signum, &signal, NULL) < 0)
		exit (1);
}
*/

void	handle_mode_interactive(int nb_signal)
{
	if (nb_signal == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_exit_status = 1;
	}
}

void	handle_mode_no_interactive(int nb_signal)
{
	if (nb_signal == SIGINT)
	{
		g_exit_status = 1;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		exit(EXIT_SUCCESS);
	}
}

int	init_signal(int nb_signal, void(*handler)(int nb))
{
	if (handler)
	{
		if (signal(nb_signal, handler) == SIG_ERR)
			return (ERROR);
	}
	else
	{
		if (signal(nb_signal, SIG_IGN) == SIG_ERR)
			return (ERROR);
	}
	return (SUCCESS);
}

int	exec_signals(int mode)
{
	void				*handle_function;
	struct termios		tc;

	handle_function = NULL;
	if (mode == MODE_INTERATIVE)
		handle_function = &handle_mode_interactive;
	else if (mode == MODE_NO_INTERACTIVE)
		handle_function = &handle_mode_no_interactive;
	tcgetattr(0, &tc);
	tc.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &tc);
	if (init_signal(SIGINT, handle_function) != SUCCESS)
		return (ERROR);
	if (init_signal(SIGQUIT, handle_function) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}

void	handle_exit_status(int *last_exit_code, int status)
{
	if (WIFEXITED(status))
		(*last_exit_code) = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			(*last_exit_code) = EXIT_CHILD_WAS_INTERRUPTED_BY_SIGINT;
		else if (WTERMSIG(status) == SIGQUIT)
		{
			(*last_exit_code) = EXIT_CHILD_WAS_INTERRUPTED_BY_SIGQUIT;
			printf("Quit: 3\n");
		}
	}
}
