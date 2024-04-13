/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro-go <pedro-go@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:34:58 by pedro-go          #+#    #+#             */
/*   Updated: 2024/04/13 15:34:59 by pedro-go         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	close_pipe_arr(int **pipes, int size)
{
	int	idx;

	idx = 0;
	while (idx < size)
	{
		close(pipes[idx][0]);
		close(pipes[idx][1]);
		idx++;
	}
}

void	close_pipes(t_minishell *minishell)
{
	if (minishell->pipes)
		close_pipe_arr(minishell->pipes, minishell->cmd_count - 1);
	if (minishell->hd_pipes)
		close_pipe_arr(minishell->hd_pipes, minishell->cmd_count);
}

int	**init_pipe_arr(int size)
{
	int	**pipes;
	int	idx;

	pipes = malloc(size * sizeof(int *));
	if (!pipes)
		return (NULL);
	ft_memset(pipes, 0, size * sizeof(int *));
	idx = 0;
	while (idx < size)
	{
		pipes[idx] = malloc(2 * sizeof(int));
		if (!pipes[idx] || pipe(pipes[idx]) == -1)
			return (NULL);
		idx++;
	}
	return (pipes);
}

int	init_pipes(t_minishell *minishell)
{
	if (minishell->cmd_count >= 2)
	{
		minishell->pipes = init_pipe_arr(minishell->cmd_count - 1);
		if (!minishell->pipes)
			return (-1);
	}
	if (minishell->cmd_count >= 1)
	{
		minishell->hd_pipes = init_pipe_arr(minishell->cmd_count);
		if (!minishell->hd_pipes)
			return (-1);
	}
	return (1);
}
