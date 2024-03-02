#include "../include/minishell.h"

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
	int		status;
	char	**envp;

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
	if (minishell->hd_pipes)
		free_pipe_arr(minishell->hd_pipes, minishell->cmd_count);
	status = minishell->last_exit_code;
	envp = minishell->envp;
	ft_memset(minishell, 0, sizeof(t_minishell));
	minishell->last_exit_code = status;
	minishell->envp = envp;
}
