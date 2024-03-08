/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 01:55:42 by brayan            #+#    #+#             */
/*   Updated: 2024/03/08 03:44:08 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_exit_status(int *last_exit_code)
{
	if (WIFEXITED(g_exit_status))
	{
		(*last_exit_code) = WEXITSTATUS(g_exit_status);
		g_exit_status = WEXITSTATUS(g_exit_status);
	}
	else if (WIFSIGNALED(g_exit_status))
	{
		if (WTERMSIG(g_exit_status) == SIGINT
			|| WTERMSIG(g_exit_status) == SIGQUIT)
		{
			(*last_exit_code) += 128;
			g_exit_status += 128;
		}
	}
}

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

void	heredoc_handle(int sig, siginfo_t *info, void *handler)
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

void	exec_signals(int mode)
{
	/*
	struct sigaction	signal;
	struct termios		tc;

	signal.sa_flags = SA_RESTART | SA_SIGINFO;
	sigemptyset(&signal.sa_mask);
	// print
	tcgetattr(0, &tc);
	tc.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &tc);
	//signal.sa_sigaction = CASO_INTERACITO;
	//signal.sa_sigaction = CASO NOINTERACTIVO;
	sigaction(SIGINT, &signal, NULL);
	sigaction(SIGQUIT, &signal, NULL);
	*/
	return ;
}
