#include "../include/minishell.h"

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

int	exec_builtin(char **argv, t_minishell *minishell)
{
	int		val;
	char	*builtin;

	val = 1;
	builtin = argv[0];
	if (ft_strequals(builtin, ECHO_CMD))
		val = builtin_echo(minishell->env, argv);
	if (ft_strequals(builtin, CD_CMD))
		val = builtin_cd(minishell, argv);
	if (ft_strequals(builtin, ENV_CMD))
		val = builtin_env(minishell);
	if (ft_strequals(builtin, EXP_CMD))
		val = builtin_export(minishell, argv);
	if (ft_strequals(builtin, PWD_CMD))
		val = builtin_pwd();
	if (ft_strequals(builtin, UNSET_CMD))
		val = builtin_unset(minishell, argv);
	return (val);
}

int	is_builtin(char *name)
{
	return (ft_strequals(name, ECHO_CMD) || ft_strequals(name, CD_CMD)
		|| ft_strequals(name, ENV_CMD) | (ft_strequals(name, EXP_CMD))
		|| ft_strequals(name, PWD_CMD) || ft_strequals(name, UNSET_CMD));
}

int	check_builtin(t_minishell *minishell)
{
	char		**argv;
	t_command	*cmd;

	if (minishell->cmd_count != 1)
		return (-1);
	cmd = minishell->commands->content;
	argv = build_str_arr_from_lst(cmd->args);
	if (!argv)
	{
		printf("%s", MALLOC_ERR_MSG);
		return (1);
	}
	if (is_builtin(argv[0]))
	{
		if (exec_builtin(argv, minishell) == -1)
			minishell->last_exit_code = EXIT_FAILURE;
		minishell->last_exit_code = EXIT_SUCCESS;
		free_str_arr(argv);
		return (1);
	}
	free_str_arr(argv);
	return (-1);
}
