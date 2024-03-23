/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:06:19 by bsaiago-          #+#    #+#             */
/*   Updated: 2024/03/07 02:40:40 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int map_builtin(char **argv, t_minishell *minishell)
{
    char	*builtin;
    int     val;

    val = 1;
    builtin = argv[0];
    if (ft_strequals(builtin, ECHO_CMD))
        val = builtin_echo(minishell->envp, argv);
    else if (ft_strequals(builtin, CD_CMD))
        val = builtin_cd(minishell, argv);
    else if (ft_strequals(builtin, ENV_CMD))
        val = builtin_env(minishell);
    else if (ft_strequals(builtin, EXP_CMD))
        val = builtin_export(minishell, argv);
    else if (ft_strequals(builtin, PWD_CMD))
        val = builtin_pwd(get_total_commands(minishell->cmd_line));
    else if (ft_strequals(builtin, UNSET_CMD))
        val = builtin_unset(minishell, argv);
    else
        val = builtin_exit(minishell, argv);
    return (val);
}

void exec_builtin(t_command *cmd, char **argv, t_minishell *minishell,
                  int exit_process)
{
	int		val;
    int     old_stdin;
    int     old_stdout;

    old_stdin = dup(STDIN_FILENO);
    old_stdout = dup(STDOUT_FILENO);
    apply_redirections(cmd->redirections, cmd->index, minishell);
    val = map_builtin(argv, minishell);
    dup2(old_stdin, STDIN_FILENO);
    close(old_stdin);
    dup2(old_stdout, STDOUT_FILENO);
    close(old_stdout);
    if (val == SUCCESS)
        val = EXIT_SUCCESS;
    else
        val = EXIT_FAILURE;
    if (exit_process)
        exit_minishell(minishell, NULL, val);
    minishell->last_exit_code = val;
}

int is_builtin(char *name)
{
	return (ft_strequals(name, ECHO_CMD) || ft_strequals(name, CD_CMD)
		|| ft_strequals(name, ENV_CMD) || (ft_strequals(name, EXP_CMD))
		|| ft_strequals(name, PWD_CMD) || ft_strequals(name, UNSET_CMD)
		|| ft_strequals(name, EXIT_CMD));
}

int	check_builtin(t_minishell *minishell)
{
	char		**argv;
	t_command	*cmd;

	if (minishell->cmd_count != SUCCESS)
		return (ERROR);
	cmd = minishell->commands->content;
	argv = build_str_arr_from_lst(cmd->args);
	if (!argv)
	{
		printf("%s", MALLOC_ERR_MSG);
        minishell->last_exit_code = EXIT_FAILURE;
		return (SUCCESS);
	}
    if (!is_builtin(argv[0]))
    {
        free_str_arr(argv);
        return (ERROR);
    }
    exec_builtin(cmd, argv, minishell, 0);
    free_str_arr(argv);
    return (SUCCESS);
}
