/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 05:20:27 by brayan            #+#    #+#             */
/*   Updated: 2024/03/05 01:27:10 by brayan           ###   ########.fr       */
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

char    *build_msg(t_minishell *minishell)
{
    char    *cwd;
    char    *home_var;
    char    msg[MAX_PATH];

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

char    *build_prompt(t_minishell *minishell)
{
    char    prompt[MAX_PATH];
    char    *msg;

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

static void	run_minishell(t_minishell *minishell)
{
    char    *prompt;

	while (1)
	{
        prompt = build_prompt(minishell);
        if (!prompt)
            exit_minishell(minishell, PROMPT_ERR_MSG, EXIT_FAILURE);
		minishell->cmd_line = readline(prompt);
        free(prompt);
		if (!minishell->cmd_line)
			continue ;
		add_history(minishell->cmd_line);
		if (tokenize_cmdline(minishell) == -1 || check_syntax(minishell) == -1
			|| process_tokens(minishell) == -1 || build_pipeline(minishell)
			== -1)
		{
			clean_minishell(minishell, NOT_CLEAN_ENV);
			continue ;
		}
		//print_minishell(minishell);
		exec_pipeline(minishell);
		clean_minishell(minishell, NOT_CLEAN_ENV);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;

	(void)argc;
	(void)argv;
	ft_memset(&minishell, 0, sizeof(minishell));
	minishell.cwd = getcwd(NULL, 0);
	if (!minishell.cwd)
		return (EXIT_FAILURE);
	if (get_cpy_env(&minishell.envp, env, get_len_env(env), IGNORE) != SUCCESS)
		return (clean_minishell(&minishell, NOT_CLEAN_ENV), EXIT_FAILURE);
	run_minishell(&minishell);
}
