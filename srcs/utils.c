/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 22:33:35 by brayan            #+#    #+#             */
/*   Updated: 2024/03/05 19:23:55 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_minishell(t_minishell *minishell, char *msg, int status)
{
	clean_minishell(minishell, CLEAN_ENV);
	if (msg)
		printf("%s\n", msg);
	exit(status);
}

int	check_syntax(t_minishell *minishell)
{
	t_list	*prev;
	t_list	*curr;

	prev = NULL;
	curr = minishell->tokens;
	while (curr)
	{
		if ((is_operator(curr->content) && (!curr->next
					|| is_operator(curr->next->content)))
			|| (ft_strequals(curr->content, PIPE) && !prev))
		{
			printf("%s", SYNTAX_ERR_MSG);
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
	char	msg[MAX_PATH];

	cwd = getcwd(NULL, 0);
	ft_memset(msg, 0, MAX_PATH);
	if (!cwd)
		return (NULL);
	home_var = ft_strdup(get_value_var_env(minishell->envp, VAR_HOME));
	if (!home_var)
		return (cwd);
	if (ft_strncmp(cwd, home_var, ft_strlen(home_var)) == 0)
	{
		msg[0] = '~';
		ft_strlcpy(msg + 1, cwd + ft_strlen(home_var), MAX_PATH - 1);
		free(cwd);
		free(home_var);
		return (ft_strdup(msg));
	}
	return (free(home_var), cwd);
}

char	*build_prompt(t_minishell *minishell)
{
	char	prompt[MAX_PATH];
	char	*msg;

	ft_memset(prompt, 0, MAX_PATH);
	msg = build_msg(minishell);
	if (!msg)
		return (NULL);
	ft_strlcpy(prompt, GREEN, MAX_PATH);
	ft_strlcpy(prompt + ft_strlen(prompt), msg,
		MAX_PATH - ft_strlen(prompt));
	ft_strlcpy(prompt + ft_strlen(prompt), DEF_COLOR,
		MAX_PATH - ft_strlen(prompt));
	prompt[ft_strlen(prompt)] = SPACE;
	return (free(msg), ft_strdup(prompt));
}
