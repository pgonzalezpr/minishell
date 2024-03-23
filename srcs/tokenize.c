#include "../include/minishell.h"

int	add_token(char *token, t_minishell *minishell)
{
	t_list	*new;

	new = ft_lstnew(token);
	if (!new)
	{
		ft_dprintf(STDERR_FILENO, "%s", MALLOC_ERR_MSG);
		return (-1);
	}
	ft_lstadd_back(&minishell->tokens, new);
	return (1);
}

char	*get_token_end(char *start)
{
	char	*current;

	current = start;
	if (*current == '|')
		return (current + 1);
	while (*current && *current != ' ' && *current != '|')
	{
		if (*current == '"' || *current == '\'')
		{
			current = ft_strchr(current + 1, *current);
			if (!current)
			{
				ft_dprintf(STDERR_FILENO, "%s", UNCLOSED_QUOTE_MSG);
				break ;
			}
		}
		current++;
	}
	return (current);
}

int	tokenize_cmdline(t_minishell *minishell)
{
	char	*start;
	char	*end;
	char	*token;

	start = minishell->cmd_line;
	while (*start)
	{
		while (*start == ' ')
			start++;
		if (!*start)
			break ;
		end = get_token_end(start);
		if (!end)
			return (-1);
		token = substring(start, end);
		if (!token)
			return (-1);
		if (add_token(token, minishell) == -1)
			return (-1);
		start = end;
	}
	return (1);
}

void	*ft_token_lstmap(t_list *lst, t_minishell *minishell)
{
	t_list	*lstnew;
	t_list	*current;
	t_list	*node;

	current = lst;
	lstnew = NULL;
	while (current)
	{
		node = ft_lstnew(expand_token(current->content, minishell));
		if (!node || !node->content)
		{
			ft_lstclear(&lstnew, (void (*)(void *))del_str);
			return (NULL);
		}
		ft_lstadd_back(&lstnew, node);
		current = current->next;
	}
	return (lstnew);
}

int	process_tokens(t_minishell *minishell)
{
	t_list	*new_tokens;

	if (!minishell->tokens)
		return (1);
	new_tokens = ft_token_lstmap(minishell->tokens, minishell);
	if (!new_tokens)
	{
		ft_dprintf(STDERR_FILENO, "%s", MALLOC_ERR_MSG);
		return (-1);
	}
	ft_lstclear(&minishell->tokens, (void (*)(void *))del_str);
	minishell->tokens = new_tokens;
	return (1);
}
