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

	arr = malloc(ft_lstsize(lst) + 1);
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

int	exec_builtin(char *builtin, char **args, t_minishell *minishell)
{
	int	val;

	val = 1;
	if (ft_strequals(builtin, ECHO_CMD))
		val = builtin_echo(minishell->env, args);
	if (ft_strequals(builtin, CD_CMD))
		val = builtin_cd(minishell, args);
	if (ft_strequals(builtin, ENV_CMD))
		val = builtin_env(minishell);
	if (ft_strequals(builtin, EXP_CMD))
		val = builtin_export(minishell, args);
	if (ft_strequals(builtin, PWD_CMD))
		val = builtin_pwd();
	if (ft_strequals(builtin, UNSET_CMD))
		val = builtin_unset(minishell, args);
	return (val);
}

int	is_builtin(char *name)
{
	return (ft_strequals(name, ECHO_CMD) || ft_strequals(name, CD_CMD)
		|| ft_strequals(name, ENV_CMD) | (ft_strequals(name, EXP_CMD))
		|| ft_strequals(name, PWD_CMD) || ft_strequals(name, UNSET_CMD));
}

void	check_builtin(char *name, char **argv, t_minishell *minishell)
{
	int val;

	if (is_builtin(name))
	{
		val = exec_builtin(name, argv, minishell);
		free_str_arr(argv);
		if (val == -1)
			exit_minishell(minishell, NULL, EXIT_FAILURE);
		exit_minishell(minishell, NULL, EXIT_SUCCESS);
	}
}