/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro-go <pedro-go@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:34:05 by pedro-go          #+#    #+#             */
/*   Updated: 2024/04/13 15:34:07 by pedro-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdlib.h>

int	redir_output(int code, char *name)
{
	int	fd;

	if (code == OUT_RED_CODE)
		fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else
		fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (fd == -1)
	{
		perror(name);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (-1);
	close(fd);
	return (1);
}

int	redir_input(char *name)
{
	int	fd;

	fd = open(name, O_RDONLY);
	if (fd == -1)
	{
		perror(name);
		return (ERROR);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
		return (ERROR);
	close(fd);
	return (1);
}

int	apply_redir(t_redirection *redir, int index, t_minishell *minishell)
{
	if (redir->code == IN_RED_CODE)
		return (redir_input(redir->name));
	if ((redir->code == OUT_RED_CODE || redir->code == OUT_RED_APP_CODE))
		return (redir_output(redir->code, redir->name));
	if (redir->code == HERE_DOC_CODE)
		return (dup2(minishell->hd_pipes[index][0], STDIN_FILENO));
	return (1);
}

int	apply_redirections(t_list *redirs, int index, t_minishell *minishell)
{
	if (index > 0)
	{
		if (dup2(minishell->pipes[index - 1][0], STDIN_FILENO) == -1)
			return (ERROR);
	}
	if (index < minishell->cmd_count - 1)
	{
		if (dup2(minishell->pipes[index][1], STDOUT_FILENO) == -1)
			return (ERROR);
	}
	while (redirs)
	{
		if (apply_redir(redirs->content, index, minishell) == ERROR)
			return (ERROR);
		redirs = redirs->next;
	}
	return (SUCCESS);
}
