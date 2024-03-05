/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:06:19 by bsaiago-          #+#    #+#             */
/*   Updated: 2024/03/05 19:04:40 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	exec_builtin(char **argv, t_minishell *minishell)
{
	int		val;
	char	*builtin;

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
		val = builtin_pwd();
	else if (ft_strequals(builtin, UNSET_CMD))
		val = builtin_unset(minishell, argv);
	else
		val = builtin_exit(minishell, argv);
	return (val);
}

static int	is_builtin(char *name)
{
	return (ft_strequals(name, ECHO_CMD) || ft_strequals(name, CD_CMD)
		|| ft_strequals(name, ENV_CMD) || (ft_strequals(name, EXP_CMD))
		|| ft_strequals(name, PWD_CMD) || ft_strequals(name, UNSET_CMD)
		|| ft_strequals(name, EXIT_CMD));
}

void	free_str_arr(char **arr)
{
	int	idx;

	if (!arr)
		return ;
	idx = 0;
	while (arr[idx])
	{
		free(arr[idx]);
		idx++;
	}
	free(arr);
}

char	**build_str_arr_from_lst(t_list *lst)
{
	char	**arr;
	t_list	*curr;
	int		idx;

	arr = malloc((ft_lstsize(lst) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	arr[ft_lstsize(lst)] = NULL;
	curr = lst;
	idx = 0;
	while (curr)
	{
		arr[idx] = ft_strdup(curr->content);
		if (!arr[idx])
		{
			free_str_arr(arr);
			break ;
		}
		idx++;
		curr = curr->next;
	}
	return (arr);
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
		return (SUCCESS);
	}
	if (is_builtin(argv[0]))
	{
		if (exec_builtin(argv, minishell) == ERROR)
			minishell->last_exit_code = EXIT_FAILURE;
		minishell->last_exit_code = EXIT_SUCCESS;
		free_str_arr(argv);
		return (SUCCESS);
	}
	free_str_arr(argv);
	return (ERROR);
}
