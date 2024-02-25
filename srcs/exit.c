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

void	free_tokens(t_token_node *tokens)
{
	t_token_node	*current;
	t_token_node	*next;

	if (!tokens)
		return ;
	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->token)
			free(current->token);
		free(current);
		current = next;
	}
}

void	free_cmd_node(t_command_node *node)
{
	if (node)
		return ;
}

void	free_pipeline(t_command_node *pipeline)
{
	t_command_node	*current;
	t_command_node	*next;

	if (!pipeline)
		return ;
	current = pipeline;
	while (current)
	{
		next = current->next;
		free_cmd_node(current);
		current = next;
	}
}

void	clean_minishell(t_minishell *minishell)
{
	if (minishell->env)
		free_env(minishell->env);
	if (minishell->cmd_line)
		free(minishell->cmd_line);
	if (minishell->tokens)
		free_tokens(minishell->tokens);
	if (minishell->pipeline)
		free_pipeline(minishell->pipeline);
	if (minishell->pipes)
		free_pipe_arr(minishell->pipes, minishell->cmd_count - 1);
	if (minishell->here_doc_pipes)
		free_pipe_arr(minishell->here_doc_pipes, minishell->cmd_count);
	ft_memset(minishell, 0, sizeof(t_minishell));
}
