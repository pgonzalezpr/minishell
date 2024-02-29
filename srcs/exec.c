#include "../include/minishell.h"

int exec_here_docs(t_minishell *minishell)
{
    if (minishell)
        return (1);
    return (-1);
}

int close_pipes(t_minishell *minishell)
{
    if (minishell)
        return (1);
    return (-1);
}

int init_pipes(t_minishell *minishell)
{
    if (minishell)
        return (1);
    return (-1);
}

void    exec_cmd(t_command *cmd, t_minishell *minishell)
{
    char    **argv;
    char    *name;

    argv = build_str_arr_from_lst(cmd->args);
    if (!argv)
        exit_minishell(minishell, MALLOC_ERR_MSG, EXIT_FAILURE);
    name = argv[0];
    check_builtin(name, argv, minishell);
}

pid_t   create_child(t_command *cmd, t_minishell *minishell)
{
    if (cmd && minishell)
        return (1);
    return (0);
}

int	exec_pipeline(t_minishell *minishell)
{
	t_list	*curr;
	pid_t	p_id;
	int		status;

	if (init_pipes(minishell) == -1 || exec_here_docs(minishell) == -1)
		return (-1);
	curr = minishell->commands;
	p_id = 0;
	while (curr)
	{
		p_id = create_child(curr->content, minishell);
		curr = curr->next;
	}
	close_pipes(minishell);
	waitpid(p_id, &status, 0);
	minishell->last_exit_code = WEXITSTATUS(status);
	return (1);
}
