/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro-go <pedro-go@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:33:56 by pedro-go          #+#    #+#             */
/*   Updated: 2024/04/13 15:33:58 by pedro-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	here_doc(int index, char *delimiter, t_minishell *minishell)
{
	char	*input;

	close(minishell->hd_pipes[index][0]);
	close(minishell->hd_pipes[index][1]);
	if (pipe(minishell->hd_pipes[index]) == -1)
		return (-1);
	while (1)
	{
		input = readline("> ");
		if (!input)
			return (-1);
		if (ft_strequals(input, delimiter))
			break ;
		if (write(minishell->hd_pipes[index][1], input, ft_strlen(input)) == -1
			||
			write(minishell->hd_pipes[index][1], "\n", 1) == -1)
		{
			free(input);
			return (-1);
		}
		free(input);
		input = NULL;
	}
	return (1);
}

int	exec_here_docs(t_minishell *minishell)
{
	t_list			*cmd_ptr;
	t_command		*cmd;
	t_list			*redir_ptr;
	t_redirection	*redir;

	cmd_ptr = minishell->commands;
	while (cmd_ptr)
	{
		cmd = (t_command *)cmd_ptr->content;
		redir_ptr = cmd->redirections;
		while (redir_ptr)
		{
			redir = (t_redirection *)redir_ptr->content;
			if (redir->code == HERE_DOC_CODE && here_doc(cmd->index,
					redir->name, minishell) == -1)
			{
				if (here_doc(cmd->index, redir->name, minishell) == -1)
					return (-1);
			}
			redir_ptr = redir_ptr->next;
		}
		cmd_ptr = cmd_ptr->next;
	}
	return (1);
}

void	exec_cmd(t_command *cmd, t_minishell *minishell)
{
	char	**argv;
	char	*path;

	argv = build_str_arr_from_lst(cmd->args);
	if (!argv)
		exit_minishell(minishell, MALLOC_ERR_MSG, EXIT_FAILURE);
	if (is_builtin(argv[0]))
		exec_builtin(cmd, argv, minishell, 1);
	if (apply_redirections(cmd->redirections, cmd->index, minishell) == ERROR)
		exit_minishell(minishell, NULL, EXIT_FAILURE);
	close_pipes(minishell);
	if (!argv[0])
	{
		exit_minishell(minishell, NULL, EXIT_SUCCESS);
	}
	path = build_cmd_path(argv[0], minishell);
	if (!*argv[0] || !path)
	{
		ft_dprintf(STDERR_FILENO, "%s: command not found\n", argv[0]);
		exit_minishell(minishell, NULL, EXIT_CMD_NOT_FOUND);
	}
	execve(path, argv, minishell->envp);
	free_str_arr(argv);
	free(path);
	exit_minishell(minishell, EXEC_ERR_MSG, EXIT_FAILURE);
}

pid_t	create_child(t_command *cmd, t_minishell *minishell)
{
	pid_t	p_id;

	p_id = fork();
	if (p_id < 0)
	{
		ft_dprintf(STDERR_FILENO, "%s", FORK_ERR_MSG);
		return (0);
	}
	else if (p_id > 0)
		return (p_id);
	else
	{
		if (exec_signals(MODE_NO_INTERACTIVE) == ERROR)
			return (ERROR);
		exec_cmd(cmd, minishell);
	}
	return (0);
}

int	exec_pipeline(t_minishell *minishell)
{
	int		status;
	t_list	*curr;
	pid_t	p_id;

	if (init_signal(SIGINT, SIG_IGN) == ERROR)
		return (ERROR);
	if (init_pipes(minishell) == -1 || exec_here_docs(minishell) == -1)
		return (-1);
	if (check_builtin(minishell) == 1)
		return (1);
	curr = minishell->commands;
	p_id = 0;
	status = EXIT_SUCCESS;
	while (curr)
	{
		p_id = create_child(curr->content, minishell);
		curr = curr->next;
	}
	close_pipes(minishell);
	waitpid(p_id, &status, 0);
	handle_exit_status(&minishell->last_exit_code, status);
	while (wait(NULL) > 0)
		continue ;
	return (1);
}
