#include "../include/minishell.h"

int	is_redirection(char *str)
{
	return (ft_strequals(str, IN_RED) || ft_strequals(str, OUT_RED)
		|| ft_strequals(str, HERE_DOC) || ft_strequals(str, OUT_RED_APP));
}

int	is_operator(char *str)
{
	return (ft_strequals(str, PIPE) || is_redirection(str));
}

void	remove_quotes(char *token)
{
	int		offset;
	char	quote;

	offset = 0;
	while (token[offset])
	{
		if (token[offset] == '"' || token[offset] == '\'')
		{
			quote = token[offset];
			ft_memmove(&token[offset], &token[offset + 1],
				ft_strlen(&token[offset + 1]) + 1);
			while (token[offset] != quote)
				offset++;
			ft_memmove(&token[offset], &token[offset + 1],
				ft_strlen(&token[offset + 1]) + 1);
		}
		else
			offset++;
	}
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
	ft_memset(arr, 0, (ft_lstsize(lst) + 1) * sizeof(char *));
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
