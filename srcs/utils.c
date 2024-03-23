/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 22:33:35 by brayan            #+#    #+#             */
/*   Updated: 2024/03/23 18:38:05 by bsaiago-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_minishell(t_minishell *minishell, char *msg, int status)
{
	clean_minishell(minishell, CLEAN_ENV);
	if (msg)
		ft_dprintf(STDERR_FILENO, "%s\n", msg);
	exit(status);
}

int	check_token(t_list *curr, t_list *prev)
{
	if (is_operator(curr->content) && !curr->next)
		return (1);
	if (ft_strequals(curr->content, PIPE) && (!prev
			|| is_operator(prev->content)))
		return (1);
	if (is_redirection(curr->content) && prev && is_redirection(prev->content))
		return (1);
	return (0);
}

int	check_syntax(t_minishell *minishell)
{
	t_list	*prev;
	t_list	*curr;
	int		err;

	prev = NULL;
	curr = minishell->tokens;
	err = 0;
	while (curr)
	{
		err = check_token(curr, prev);
		if (err)
		{
			ft_dprintf(STDERR_FILENO, "%s", SYNTAX_ERR_MSG);
			return (-1);
		}
		prev = curr;
		curr = curr->next;
	}
	return (1);
}

char	*build_msg(t_minishell *minishell)
{
	char	*cwd;
	char	*home_var;
	char	msg[MAX];

	cwd = getcwd(NULL, 0);
	ft_memset(msg, 0, MAX);
	if (!cwd)
		return (NULL);
	home_var = ft_strdup(get_value_var_env(minishell->envp, VAR_HOME));
	if (!home_var)
		return (cwd);
	if (ft_strncmp(cwd, home_var, ft_strlen(home_var)) == 0)
	{
		msg[0] = '~';
		ft_strlcpy(msg + 1, cwd + ft_strlen(home_var), MAX - 1);
		free(cwd);
		free(home_var);
		return (ft_strdup(msg));
	}
	return (free(home_var), cwd);
}

char	*build_prompt(t_minishell *minishell)
{
	char	prompt[MAX];
	char	*msg;

	ft_memset(prompt, 0, MAX);
	msg = build_msg(minishell);
	if (!msg)
		return (NULL);
	ft_strlcpy(prompt, GREEN, MAX);
	ft_strlcpy(prompt + ft_strlen(prompt), msg, MAX - ft_strlen(prompt));
	ft_strlcpy(prompt + ft_strlen(prompt), DEF_COLOR, MAX - ft_strlen(prompt));
	prompt[ft_strlen(prompt)] = EMPTY;
	return (free(msg), ft_strdup(prompt));
}

/*
* PRE: cmd_line != NULL
* POST: Devuelve el total de comandos ingresados.
*/
int	get_total_commands(char *cmd_line)
{
	int	total;
	int	in_command;
	int	i;

	if (!cmd_line)
		return (0);
	i = -1;
	total = 0;
	in_command = 0;
	while (cmd_line[++i])
	{
		if (cmd_line[i] != EMPTY && !in_command)
		{
			total++;
			in_command = 1;
		}
		else if (cmd_line[i] == EMPTY && in_command)
			in_command = 0;
	}
	return (total);
}
