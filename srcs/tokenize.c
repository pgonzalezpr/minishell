#include "../include/minishell.h"

t_token_node	*get_token_node(char *begin, char *end)
{
	char			*token;
	t_token_node	*token_node;
	size_t			len;

	len = (size_t)(end - begin);
	token = malloc((len + 1) * sizeof(char));
	if (!token)
		return (NULL);
	ft_strlcpy(token, begin, len + 1);
	token_node = malloc(sizeof(t_token_node));
	if (!token_node)
	{
		free(token);
		return (NULL);
	}
	token_node->token = token;
	token_node->next = NULL;
	return (token_node);
}

void	add_token(char *begin, char *end, t_minishell *minishell)
{
	t_token_node	*token_node;
	t_token_node	*current;

	if (begin == end)
		return ;
	token_node = get_token_node(begin, end);
	if (!token_node)
		exit_minishell(minishell, "Tokenize error\n", EXIT_FAILURE);
	if (minishell->tokens == NULL)
		minishell->tokens = token_node;
	else
	{
		current = minishell->tokens;
		while (current->next)
			current = current->next;
		current->next = token_node;
	}
}

size_t	get_token_len(char *current, t_minishell *minishell)
{
	char	quote;
	size_t	offset;

	offset = 0;
	while (current[offset] && current[offset] != ' ' && current[offset] != '|')
	{
		if (current[offset] == '"' || current[offset] == '\'')
		{
			quote = current[offset];
			offset++;
			while (current[offset] && current[offset] != quote)
				offset++;
			if (!current[offset])
				exit_minishell(minishell, "Error. Unclosed quote\n",
					EXIT_FAILURE);
		}
		offset++;
	}
	return (offset);
}

void	process_tokens(t_minishell *minishell)
{
	t_token_node	*current;

	current = minishell->tokens;
	while (current)
	{
		replace_env_vars(current, minishell);
		remove_quotes(current);
		printf("%s\n", current->token);
		current = current->next;
	}
}

void	tokenize_cmd_line(t_minishell *minishell)
{
	char	*begin;
	char	*current;

	current = minishell->cmd_line;
	while (*current)
	{
		while (*current == ' ')
			current++;
		begin = current;
		current += get_token_len(current, minishell);
		add_token(begin, current, minishell);
		if (!*current)
			break ;
		if (*current == '|')
		{
			begin = current;
			current++;
			add_token(begin, current, minishell);
		}
	}
	process_tokens(minishell);
}
