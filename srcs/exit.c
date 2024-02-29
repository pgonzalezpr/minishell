#include "../include/minishell.h"

void	free_pipe_arr(int **arr, size_t size)
{
	size_t	i;

	if (!arr)
		return ;
	i = 0;
	while (i < size)
	{
		if (arr[i])
			free(arr[i]);
		i++;
	}
	free(arr);
}

void	del_str(char *str)
{
	if (str)
		free(str);
}

void	del_redir(t_redirection *redir)
{
	if (!redir)
		return ;
	if (redir->name)
		free(redir->name);
	free(redir);
}

void	del_command(t_command *command)
{
	if (!command)
		return ;
	ft_lstclear(&command->args, (void (*)(void *))del_str);
	ft_lstclear(&command->redirections, (void (*)(void *))del_redir);
	free(command);
}

void	clean_minishell(t_minishell *minishell)
{
    int status;

	if (minishell->env)
		free_env(minishell->env);
	if (minishell->cmd_line)
		free(minishell->cmd_line);
	if (minishell->tokens)
		ft_lstclear(&minishell->tokens, (void (*)(void *))del_str);
	if (minishell->commands)
		ft_lstclear(&minishell->commands, (void (*)(void *))del_command);
	if (minishell->pipes)
		free_pipe_arr(minishell->pipes, minishell->cmd_count - 1);
	if (minishell->here_doc_pipes)
		free_pipe_arr(minishell->here_doc_pipes, minishell->cmd_count);
    status = minishell->last_exit_code;
	ft_memset(minishell, 0, sizeof(t_minishell));
    minishell->last_exit_code = status;
}
