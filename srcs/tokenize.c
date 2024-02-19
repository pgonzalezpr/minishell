#include "../include/minishell.h"

t_token_node	*get_token_node(char *token)
{
	t_token_node	*token_node;

	if (!token)
		return (NULL);
	token_node = malloc(sizeof(t_token_node));
	if (!token_node)
	{
		printf("%s\n", MALLOC_ERR_MSG);
		return (NULL);
	}
	token_node->token = token;
	token_node->next = NULL;
	return (token_node);
}

int	add_token(char *token, t_minishell *minishell)
{
	t_token_node	*token_node;
	t_token_node	*current;

	token_node = get_token_node(token);
	if (!token_node)
	{
		free(token);
		return (-1);
	}
	if (minishell->tokens == NULL)
		minishell->tokens = token_node;
	else
	{
		current = minishell->tokens;
		while (current->next)
			current = current->next;
		current->next = token_node;
	}
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
				printf("%s\n", UNCLOSED_QUOTE_MSG);
				break ;
			}
		}
		current++;
	}
	return (current);
}

int	process_tokens(t_minishell *minishell)
{
	t_token_node	*current;
	char			*expanded_token;

	current = minishell->tokens;
	while (current)
	{
		expanded_token = expand_token(current->token);
		if (!expanded_token)
			return (-1);
		remove_quotes(expanded_token);
		free(current->token);
		current->token = expanded_token;
		printf("%s\n", current->token);
		current = current->next;
	}
	return (1);
}

int	tokenize_cmd_line(t_minishell *minishell)
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
